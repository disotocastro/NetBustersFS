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
    }else{
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

void SistemaArchivosFAT::escribir(const std::string& nombreArchivo,
                                  std::string dato) {
  int posicion = buscar(nombreArchivo);
  if (posicion != -1) {
    Archivo& archivo = directorio[posicion];
    int cursor = archivo.cursor;
    int posAnterior = -1;
    int unidadCursor = dato.length();
    int auxiliarCursor = 0;  // se utiliza cunado se quierren poner las
                             // posiciones del FAT y el cursor es
    if (cursor == 0) {
      for (int i = 0; i < (TAM_BLOQUE) && (!dato.empty()); i++) {
        if(unidad[i].marco[0]== '\0') {
          if (directorio[posicion].bloqueInicio == -1) {
            // Asigna el primer bloque al inicio del archivo
            directorio[posicion].bloqueInicio = i;
          } else {
            // Actualiza FAT con la posición anterior
            tablaBloques[posAnterior] = i;
          }
          // actualiza la posicion anterior
          posAnterior = i;
          // recorre el FAT y escribe ahi
          for (int j = 0; j < TAM_BLOQUE && (!dato.empty()); j++) {
            if (!dato.empty()) {
              // escribe los datos
              unidad[i].marco[j] = dato[0];
              dato.erase(0, 1);
            }
          }
        }
      }
    } else {
      if (cursor != 0){
        // en el caso que el cursor no este acomodado
        for (int i = cursor / TAM_BLOQUE; i < TAM_BLOQUE && (!dato.empty()); i++) {
          // Actualiza FAT con la posición anterior
          posAnterior = i - 1;
          std::cout<<posAnterior;
          tablaBloques[posAnterior] = i;
          posAnterior = i;
          // axiliar para sobreescribir
          bool auxMarco = false;

          // escribe en la unidad la informacion de datos y hash
          for (int j = 0; j < TAM_BLOQUE && !dato.empty(); ++j) {
            // condicion para que inicie exactamente donde esta el puntero
            if (i == (cursor / TAM_BLOQUE) && j == (cursor % TAM_BLOQUE)) {
              if (!dato.empty()) {
                unidad[i].marco[j] = dato[0];
                dato.erase(0, 1);
                auxMarco = true;
              }
            } else {
              // si ya sobreescribio en la primera letra, entonces que siga
              if (auxMarco) {
                if (!dato.empty()) {
                  unidad[i].marco[j] = dato[0];
                  dato.erase(0, 1);
                }
              }
            }
          }
        }
      }
    }
    directorio[posicion].bloqueFin = posAnterior;
    directorio[posicion].cursor += unidadCursor;
  } else {
    std::cout<< " NO se pudo escribir el archivo" << std::endl;
  }
}

void SistemaArchivosFAT::cambiarCursor(const std::string& nombreArchivo, int pos){
  for (int i = 0; i < cantidadDirectorios; i++) {
    if (directorio[i].nombre == nombreArchivo) {
      //imprimirArchivoEncontrado(nombreArchivo);
      directorio[i].cursor = pos;
    }
  }
}