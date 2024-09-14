#include "SistemaArchivosFAT.hpp"

#include <cstring>
#include <iostream>

// Constructor
SistemaArchivosFAT::SistemaArchivosFAT() {
  // Implementar
  // cantidad de directorios
  cantidadDirectorios = 0;
  // tabla de bloques
  for (int i = 0; i < TAM_TABLA; ++i) {
    tablaBloques[i] = -1;  // se inicializan todos los espacios en el FAT en -1
  }
  // unidad
  for (int i = 0; i < TAM_UNIDAD / TAM_BLOQUE; ++i) {
    // Inicializa cada frame de la como vacia
    for (int j = 0; j < TAM_BLOQUE; ++j) {
      unidad[i].marco[j] =
          '\0';  // se inicializan todos los bytes de cada frame nulo
    }
  }

 // directorio.resize(10);  // Se crea un directorio con tamaño fijo de 5
}

// verificar despues si la funcionalidad se deja o no, podria ser esta la idea de estos metodos
void SistemaArchivosFAT::abrir(const std::string& nombreArchivo, bool verbose) {
  int posicion = encontrarArchivo(nombreArchivo);
  if (verbose){
     if (posicion != -1) {
      if (directorio[posicion].abierto) {
        std::cout << "El archivo '" << nombreArchivo << "' ya está abierto." << std::endl;
      } else {
        directorio[posicion].abierto = true;  // Marcar el archivo como abierto
        std::cout << "El archivo '" << nombreArchivo << "' ha sido abierto." << std::endl;
      }
    } else {
      std::cout << "Error: Archivo '" << nombreArchivo << "' no encontrado." << std::endl;
    }
  
  } else{
    if(posicion != -1) {
      if (directorio[posicion].abierto == false){
          directorio[posicion].abierto = true;  // Marcar el archivo como abierto
      }
    }
  }
}

// verificar despues si la funcionalidad se deja o no, podria ser esta la idea de estos metodos
void SistemaArchivosFAT::cerrar(const std::string& nombreArchivo) {
  int posicion = encontrarArchivo(nombreArchivo);

  if (posicion != -1) {
    if (!directorio[posicion].abierto) {
      std::cout << "El archivo '" << nombreArchivo << "' ya está cerrado." << std::endl;
    } else {
      directorio[posicion].abierto = false;  // Marcar el archivo como cerrado
      std::cout << "El archivo '" << nombreArchivo << "' ha sido cerrado." << std::endl;
    }
  } else {
    std::cout << "Error: Archivo '" << nombreArchivo << "' no encontrado." << std::endl;
  }
}

void SistemaArchivosFAT::crear(const std::string& nombreArchivo) {

  if (cantidadDirectorios == 0){
    directorio[0] = Archivo();
    directorio[0].nombre = nombreArchivo;
    cantidadDirectorios++;
  } else {
    directorio[cantidadDirectorios] = Archivo();
    directorio[cantidadDirectorios].nombre = nombreArchivo;
    cantidadDirectorios++;
  }

}

void SistemaArchivosFAT::crearConArchivos(const std::string& nombreArchivo,
                               std::vector<char>& datos) {
  // int posAnterior =
  //     -1;  // Iniciar con -1 para indicar que no hay posición anterior

  // for (size_t i = 0; i < directorio.size(); ++i) {
  //   // Busca espacio vacío en el directorio
  //   if (directorio[i].nombre.empty()) {
  //     directorio[i].nombre = nombreArchivo;  // Asigna nombre en el directorio
  //     directorio[i].bloqueInicio = -1;       // Inicializa el bloque de inicio
  //     directorio[i].abierto = false;  // Inicializa el archivo como cerrado

  //     // Ingresar datos a la unidad
  //     for (int j = 0; j < TAM_UNIDAD / TAM_BLOQUE && !datos.empty(); ++j) {
  //       // Si se encuentra un marco vacío en la unidad
  //       if (unidad[j].marco[0] == '\0') {
  //         if (directorio[i].bloqueInicio == -1) {
  //           // Asigna el primer bloque al inicio del archivo
  //           directorio[i].bloqueInicio = j;
  //         } else {
  //           // Actualiza FAT con la posición anterior
  //           tablaBloques[posAnterior] = j;
  //         }
  //         posAnterior = j;

  //         // Guardar los datos en el frame
  //         escribir(j, datos);
  //       }
  //     }
  //     // Asigna el bloque final al final del archivo
  //     directorio[i].bloqueFin = posAnterior+1;
  //     // Sale del bucle después de encontrar un espacio vacío y asignar los
  //     // datos
  //     break; 
  //   }
  // }

}

void SistemaArchivosFAT::leer(const std::string& nombreArchivo) {
  int posicionOriginal = encontrarArchivo(nombreArchivo);
  
  if (posicionOriginal != -1) {
    // Verificar si el archivo está abierto antes de leerlo
    if (!directorio[posicionOriginal].abierto) {
      std::cout << "Error: El archivo '" << nombreArchivo << "' no está abierto." << std::endl;
      return;
    }

    int marco = directorio[posicionOriginal].bloqueInicio;
    int bloqueFinal = directorio[posicionOriginal].bloqueFin;

    std::cout << "Leyendo contenido de " << nombreArchivo << ": " << std::endl;
    for (marco; marco <= bloqueFinal; marco++) {
      for (int i = 0; i < TAM_BLOQUE; i++) {
          std::cout << unidad[marco].marco[i];
      }
    }

    std::cout << std::endl;
  } else {
    std::cout << "Error: Archivo '" << nombreArchivo << "' no encontrado." << std::endl;
  }
}

void SistemaArchivosFAT::escribir(const std::string& nombreArchivo, std::vector<char>& datos) {
  
  int posicion = encontrarArchivo(nombreArchivo);
  int posAnterior =
    -1;  // Iniciar con -1 para indicar que no hay posición anterior
   // Ingresar datos a la unidad
  for (int j = 0; j < TAM_UNIDAD / TAM_BLOQUE && !datos.empty(); ++j) {
    // Si se encuentra un marco vacío en la unidad
    for(int k = 0; k < TAM_BLOQUE && !datos.empty(); k++){
       if (unidad[j].marco[k] == '\0') {
        if (directorio[posicion].bloqueInicio == -1) {
          // Asigna el primer bloque al inicio del archivo
          directorio[posicion].bloqueInicio = j;
        } else {
          // Actualiza FAT con la posición anterior
          tablaBloques[posAnterior] = j;
        }
        posAnterior = j;

        // Guardar los datos en el frame
        for (int i = k; i < TAM_BLOQUE && !datos.empty(); ++i) {
          // Revisa que sea un marco vacío
          if (unidad[j].marco[i] == '\0') {
            // Asigna el char en el espacio vacío del frame
            unidad[j].marco[i] = datos[0];
            // Borra el primer elemento del vector
            datos.erase(datos.begin());
          }
        }
      }
    }
  }
  directorio[posicion].bloqueFin = posAnterior+1;
}

void SistemaArchivosFAT::imprimir(){
  for(int i = 0 ; i<10; i++){
    std::cout<<tablaBloques[i]<<std::endl;
  }

  for(int i = 0 ; i<10; i++){
    for(int j = 0 ; j<8; j++){
    std::cout<<unidad[i].marco[j]<<" ";
  }
  }
}

// verificar despues si la funcionalidad se deja o no, podria ser esta la idea de estos metodos
void SistemaArchivosFAT::buscar(const std::string& nombreArchivo) {
// Es una logica mas informativa de donde esta el archivo y su bloque y demas
  int posicion = encontrarArchivo(nombreArchivo);

  if (posicion != -1) {
    std::cout << "Archivo encontrado: " << directorio[posicion].nombre << std::endl;
    std::cout << "Bloque de inicio: " << directorio[posicion].bloqueInicio << std::endl;
    std::cout << "Bloque final: " << directorio[posicion].bloqueFin << std::endl;
    std::cout << "Estado: " << (directorio[posicion].abierto ? "Abierto" : "Cerrado") << std::endl;
  } else {
    std::cout << "Error: Archivo '" << nombreArchivo << "' no encontrado." << std::endl;
  }
}

void SistemaArchivosFAT::borrar(const std::string& nombreArchivo) {
  int siguienteBloque = 0;
  int bloqueInicio = 0;

  for (size_t i = 0; i < cantidadDirectorios; i++) {
    // Si existe el archivo en el directorio
    if (directorio[i].nombre == nombreArchivo) {
      bloqueInicio = directorio[i].bloqueInicio;

      // Liberar los bloques
      while (bloqueInicio != -1) {
        // Se incia el borrado en el primer bloque de la tabla
        siguienteBloque = tablaBloques[bloqueInicio];
        // Se le asigna -1
        tablaBloques[bloqueInicio] = -1;
        // Se elimina siguiente bloque
        bloqueInicio = siguienteBloque;
      }

      // Limpiar los valores del directorio
      directorio[i].nombre.clear();
      directorio[i].bloqueInicio = -1;

      std::cout << "Archivo '" << nombreArchivo << "' borrado exitosamente."
                << std::endl;
      return;
    }
  }

  std::cout << "Error: Archivo '" << nombreArchivo << "' no encontrado."
            << std::endl;
}

void SistemaArchivosFAT::adjuntar(const std::string& nombreArchivo,
                                  std::vector<char>& datos) {
  // Buscar el archivo
  int posicionOriginal = encontrarArchivo(nombreArchivo);
  int marco = -1;
 
  // Ingresar datos a la unidad
  if (posicionOriginal != -1) {
    int posicionActual = -1;

    marco = directorio[posicionOriginal].bloqueFin;
    for (marco; marco < TAM_UNIDAD / TAM_BLOQUE && !datos.empty(); ++marco) {
      posicionActual = marco;

      //Actualizar tabla de bloques
      tablaBloques[posicionActual-1] = marco;

      escribirAdjuntando(marco, datos);
    }
    directorio[posicionOriginal].bloqueFin = posicionActual;
  };
}


void SistemaArchivosFAT::escribirAdjuntando(size_t marco, std::vector<char>& datos) {
  for (int i = 0; i < TAM_BLOQUE && !datos.empty(); ++i) {
    // Revisa que sea un marco vacío
    if (unidad[marco].marco[i] == '\0') {
      // Asigna el char en el espacio vacío del frame
      unidad[marco].marco[i] = datos[0];
      // Borra el primer elemento del vector
      datos.erase(datos.begin());
    }
  }
}

void SistemaArchivosFAT::renombrar(const std::string& nombreArchivo,
                                   const std::string& nuevoNombre) {
  // Buscar el archivo original
  int posicionOriginal = encontrarArchivo(nombreArchivo);

  // Si no se encuentra el archivo original, mostrar error
  if (posicionOriginal == -1) {
    std::cout << "Error: Archivo '" << nombreArchivo << "' no encontrado."
              << std::endl;
    return;
  }

  // Verificar si el nuevo nombre ya existe
  int posicionNuevoNombre = encontrarArchivo(nuevoNombre);
  if (posicionNuevoNombre != -1) {
    std::cout << "Error: El archivo '" << nuevoNombre << "' ya existe."
              << std::endl;
    return;
  }

  // Renombrar el archivo
  directorio[posicionOriginal].nombre = nuevoNombre;
  std::cout << "Archivo '" << nombreArchivo
            << "' ha sido renombrado exitosamente a: " << nuevoNombre
            << std::endl;
}

void SistemaArchivosFAT::listar() {
  for (size_t i = 0; i < cantidadDirectorios; i++) {
 
      std::cout << "Contenido de la dirección: " << i << " | "
                << "Nombre del archivo: " << directorio[i].nombre
                << " | Bloque de inicio: " << directorio[i].bloqueInicio
                << " | Bloque final: " << directorio[i].bloqueFin
                << " | Estado: " << (directorio[i].abierto ? " Abierto" : " Cerrado")
                << std::endl;
    
    //  else {
    //   std::cout << "Directorio vacío en la posición: " << i << std::endl;
    // }
  }
}

int SistemaArchivosFAT::encontrarArchivo(const std::string& nombreArchivo) {
  for (size_t i = 0; i < cantidadDirectorios; i++) {
    if (directorio[i].nombre == nombreArchivo) {
      std::cout << "Archivo '" << nombreArchivo << "' encontrado." << std::endl;
      return i;  // Retorna la posición en el directorio si se encuentra
    }
  }

  std::cout << "Error: Archivo '" << nombreArchivo << "' no encontrado."
            << std::endl;
  return -1;  // Retorna -1 si no se encuentra el archivo
}

int SistemaArchivosFAT::asignarBloques(int tamano) {
  // Implementar
}

void SistemaArchivosFAT::liberarBloques(int bloqueInicio) {
  // Implementar
}
