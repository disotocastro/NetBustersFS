#include "SistemaArchivosFAT.hpp"

// Constructor
SistemaArchivosFAT::SistemaArchivosFAT() {
  // cantidad de directorios
  cantidadDirectorios = 0;
  // inicializar valores
  for (int i = 0; i < TAM_TABLA; ++i) {
    // tabla de bloques
    tablaBloques[i] = 0;
    // inicializar directorios
    directorio[i] = Archivo();
    // Inicializa cada frame de la como vacia
    for (int j = 0; j < TAM_BLOQUE; ++j) {
      unidad[i].marco[j] =
          '\0';  // se inicializan todos los bytes de cada frame nulo
    }
  }
}

bool SistemaArchivosFAT::crear(const std::string& nombreArchivo) {
  bool result = true;
  while (result) {
    if (directorio[cantidadDirectorios].nombre == "") {
      directorio[cantidadDirectorios].nombre = nombreArchivo;
      cantidadDirectorios++;
      result = false;
    }
  }
  return !result;
}

bool SistemaArchivosFAT::abrir(const std::string& nombreArchivo) {
  int posicion = buscar(nombreArchivo);
  bool result = false;
  if (posicion != -1) {
    if (!directorio[posicion].abierto) {
      directorio[posicion].abierto = true;
      result = true;
    }
  }
  return result;
}

int SistemaArchivosFAT::buscar(const std::string& nombreArchivo) {
  for (int i = 0; i < TAM_TABLA; i++) {
    if (directorio[i].nombre == nombreArchivo) {
      return i;
    }
  }
  return -1;
}

bool SistemaArchivosFAT::cerrar(const std::string& nombreArchivo) {
  int posicion = buscar(nombreArchivo);
  bool result = false;
  if (posicion != -1) {
    if (directorio[posicion].abierto) {
      directorio[posicion].abierto = false;
      result = true;
    }
  }
  return result;
}

void SistemaArchivosFAT::listar() {
  if (cantidadDirectorios == 0) {
    std::cout << "No hay archivos en el sistema." << std::endl;
    return;
  }

  for (int i = 0; i < cantidadDirectorios; i++) {
    std::cout << "Contenido de la dirección: " << i
              << " | Nombre del archivo: " << directorio[i].nombre
              << " | Bloque de inicio: " << directorio[i].bloqueInicio
              << " | Bloque final: " << directorio[i].bloqueFin << " | Estado: "
              << (directorio[i].abierto ? "Abierto" : "Cerrado") << std::endl;
  }
}

bool SistemaArchivosFAT::renombrar(const std::string& nombreArchivo,
                                   const std::string& nuevoNombre) {
  // Buscar el archivo original
  int posicionOriginal = buscar(nombreArchivo);
  bool result = true;

  if (posicionOriginal != -1) {
    int posicionNueva = buscar(nuevoNombre);
    if (posicionNueva == -1) {
      directorio[posicionOriginal].nombre = nuevoNombre;
    } else {
      result = false;
    }
  } else if (posicionOriginal == -1) {
    result = false;
  }
  return result;
}

void SistemaArchivosFAT::imprimir() {
  std::cout << "Tabla de asignación de bloques (FAT):" << std::endl;
  for (int i = 0; i < 10; ++i) {
    std::cout << "Bloque " << i << ": " << tablaBloques[i] << std::endl;
  }

  std::cout << "\nContenido de los bloques:" << std::endl;
  for (int i = 0; i < 10; ++i) {
    std::cout << "Bloque " << i << ": ";
    for (int j = 0; j < 256; ++j) {
      if (unidad[i].marco[j] != '\0') {
        std::cout << unidad[i].marco[j] << " ";
      }
    }
    std::cout << std::endl;
  }
}

void SistemaArchivosFAT::escribir(const std::string& nombreArchivo, std::string dato) {
  int posicion = buscar(nombreArchivo);
  if (posicion != -1) {
    Archivo& archivo = directorio[posicion];
    int cursor = archivo.cursor;  // Posición del cursor en el archivo
    int bloqueActual = archivo.bloqueInicio;  // Bloque donde inicia el archivo
    int unidadCursor = dato.length();  // Número de caracteres a escribir
    int tamBloqueLibre;  // Espacio libre en el bloque actual

    // Si el archivo no tiene bloques asignados, asignar el primer bloque
    if (bloqueActual == -1) {
      for (int i = 0; i < TAM_TABLA; ++i) {
        if (tablaBloques[i] == 0) {  // Encuentra un bloque libre
          bloqueActual = i;
          directorio[posicion].bloqueInicio = i;
          tablaBloques[i] = -1;  // Marcar como el último bloque del archivo
          break;
        }
      }
    }

    // Recorrer todos los bloques ya asignados
    while (cursor > TAM_BLOQUE) {
      bloqueActual = tablaBloques[bloqueActual];  // Mover al siguiente bloque
      cursor -= TAM_BLOQUE;
    }

    while (!dato.empty()) {
      tamBloqueLibre = TAM_BLOQUE - (cursor % TAM_BLOQUE);  // Espacio restante en el bloque actual

      // Escribir datos en el bloque actual
      for (int i = cursor % TAM_BLOQUE; i < TAM_BLOQUE && !dato.empty(); ++i) {
        unidad[bloqueActual].marco[i] = dato[0];
        dato.erase(0, 1);  // Eliminar el carácter escrito
        archivo.tamaño++;
      }

      // Si aún quedan datos por escribir, asignar un nuevo bloque
      if (!dato.empty()) {
        int nuevoBloque = -1;
        for (int i = 0; i < TAM_TABLA; ++i) {
          if (tablaBloques[i] == 0) {  // Encuentra un bloque libre
            nuevoBloque = i;
            tablaBloques[bloqueActual] = nuevoBloque;  // Enlazar con el bloque actual
            tablaBloques[nuevoBloque] = -1;  // Marcar como el último bloque
            bloqueActual = nuevoBloque;
            break;
          }
        }

        if (nuevoBloque == -1) {
          std::cout << "No hay bloques disponibles para escribir más datos." << std::endl;
          return;
        }
      }

      // Reiniciar cursor para el nuevo bloque
      cursor = 0;
    }

    // Actualizar bloque final y cursor del archivo
    directorio[posicion].bloqueFin = bloqueActual;
    directorio[posicion].cursor += unidadCursor;
  } else {
    std::cout << "No se pudo escribir en el archivo, no existe." << std::endl;
  }
}

void SistemaArchivosFAT::cambiarCursor(const std::string& nombreArchivo,
                                       int pos) {
  for (int i = 0; i < cantidadDirectorios; i++) {
    if (directorio[i].nombre == nombreArchivo) {
      // imprimirArchivoEncontrado(nombreArchivo);
      directorio[i].cursor = pos;
    }
  }
}

std::string SistemaArchivosFAT::leer(const std::string& nombreArchivo,
                                     int cantidadLeer) {
  int posicion = buscar(nombreArchivo);
  sincronizarCursor(posicion, 0);
  if (posicion == -1) {
    return "";
  }

  Archivo& archivo = directorio[posicion];
  // Evitar lectura fuera del tamaño del archivo
  if (archivo.cursor + cantidadLeer > archivo.tamaño) {
    cantidadLeer = archivo.tamaño - archivo.cursor;
  }

  if (cantidadLeer <= 0) {
    return "";
  }

  int cursor = archivo.cursor;
  int bloqueActual = archivo.bloqueInicio;
  std::string datosLeidos;
  int bytesLeidos = 0;

  // Recorrer la FAT para llegar al bloque donde está el cursor
  while ((bytesLeidos < cursor) && bloqueActual != -1) {
    bloqueActual = tablaBloques[bloqueActual];
    bytesLeidos += TAM_BLOQUE;
  }

  // Calcular el offset dentro del bloque actual
  int offsetEnBloque = cursor % TAM_BLOQUE;
  bytesLeidos = 0;

  while ((bytesLeidos < cantidadLeer) && bloqueActual != -1) {
    // Calcular cuántos bytes quedan por leer en este bloque
    int bytesRestantesEnBloque = TAM_BLOQUE - offsetEnBloque;
    int bytesPorLeer =
        std::min(bytesRestantesEnBloque, cantidadLeer - bytesLeidos);

    // Leer los datos del bloque actual

    for (int i = offsetEnBloque; i < offsetEnBloque + bytesPorLeer; i++) {
      datosLeidos += unidad[bloqueActual].marco[i];
    }

    bytesLeidos += bytesPorLeer;
    offsetEnBloque = 0;  // Para los siguientes bloques, leer desde el inicio
    // Mover al siguiente bloque en la FAT
    bloqueActual = tablaBloques[bloqueActual];
  }

  // Actualizar el cursor
  archivo.cursor += bytesLeidos;

  return datosLeidos;
}

void SistemaArchivosFAT::sincronizarCursor(int archivo, const int posicion) {
  directorio[archivo].cursor = posicion;
}