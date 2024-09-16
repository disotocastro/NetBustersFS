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
  if (posicion != -1) {
    if (directorio[posicion].abierto) {
      if (verbose) {
        std::cout << "El archivo '" << nombreArchivo << "' ya está abierto." << std::endl;
      }
    } else {
      directorio[posicion].abierto = true;  // Marcar el archivo como abierto
      if (verbose) {
        std::cout << "El archivo '" << nombreArchivo << "' ha sido abierto." << std::endl;
      }
    }
  } else {
    if (verbose) {
      std::cout << "Error: Archivo '" << nombreArchivo << "' no encontrado." << std::endl;
    }
  }
}

// verificar despues si la funcionalidad se deja o no, podria ser esta la idea de estos metodos
void SistemaArchivosFAT::cerrar(const std::string& nombreArchivo, bool verbose) {
  int posicion = encontrarArchivo(nombreArchivo);
  if (posicion != -1) {
    if (!directorio[posicion].abierto) {
      if (verbose) {
        std::cout << "El archivo '" << nombreArchivo << "' ya está cerrado." << std::endl;
      }
    } else {
      directorio[posicion].abierto = false;  // Marcar el archivo como cerrado
      if (verbose) {
        std::cout << "El archivo '" << nombreArchivo << "' ha sido cerrado." << std::endl;
      }
    }
  } else {
    if (verbose) {
      std::cout << "Error: Archivo '" << nombreArchivo << "' no encontrado." << std::endl;
    }
  }
}

void SistemaArchivosFAT::crear(const std::string& nombreArchivo, bool verbose) {
  if (cantidadDirectorios >= TAM_UNIDAD / TAM_BLOQUE) {
    if (verbose) {
      std::cout << "Error: No se pueden crear más archivos. Límite alcanzado." << std::endl;
    }
    return;
  }

  // Verificar si el archivo ya existe
  int posicion = encontrarArchivo(nombreArchivo);
  if (posicion != -1) {
    if (verbose) {
      std::cout << "Error: El archivo '" << nombreArchivo << "' ya existe." << std::endl;
    }
    return;
  }

  // Crear el archivo vacío
  directorio[cantidadDirectorios] = Archivo();
  directorio[cantidadDirectorios].nombre = nombreArchivo;
  directorio[cantidadDirectorios].bloqueInicio = -1;
  directorio[cantidadDirectorios].bloqueFin = -1;
  cantidadDirectorios++;

  if (verbose) {
    std::cout << "Archivo '" << nombreArchivo << "' creado correctamente (sin datos)." << std::endl;
  }
}


void SistemaArchivosFAT::crear(const std::string& nombreArchivo, std::vector<char>& datos, bool verbose) {
    if (cantidadDirectorios >= TAM_UNIDAD / TAM_BLOQUE) {
        if (verbose) {
            std::cout << "Error: No se pueden crear más archivos. Límite alcanzado." << std::endl;
        }
        return;
    }

    // Verificar si el archivo ya existe
    int posicion = encontrarArchivo(nombreArchivo);
    if (posicion != -1) {
        if (verbose) {
            std::cout << "Error: El archivo '" << nombreArchivo << "' ya existe." << std::endl;
        }
        return;
    }

    // Crear el archivo
    directorio[cantidadDirectorios] = Archivo();
    directorio[cantidadDirectorios].nombre = nombreArchivo;
    directorio[cantidadDirectorios].bloqueInicio = -1;
    directorio[cantidadDirectorios].bloqueFin = -1;

    // Asignar bloques y escribir los datos
    escribir(nombreArchivo, datos, verbose);  // Utilizar el método existente para escribir los datos
    cantidadDirectorios++;

    if (verbose) {
        std::cout << "Archivo '" << nombreArchivo << "' creado correctamente y datos escritos." << std::endl;
    }
}
void SistemaArchivosFAT::leer(const std::string& nombreArchivo, bool verbose) {
    int posicionOriginal = encontrarArchivo(nombreArchivo);
    if (posicionOriginal != -1) {
        if (!directorio[posicionOriginal].abierto) {
            if (verbose) {
                std::cout << "Error: El archivo '" << nombreArchivo << "' no está abierto." << std::endl;
            }
            return;
        }

        int bloqueActual = directorio[posicionOriginal].bloqueInicio;  // Comenzamos desde el bloque de inicio
        if (bloqueActual == -1) {
            if (verbose) {
                std::cout << "Error: El archivo '" << nombreArchivo << "' está vacío." << std::endl;
            }
            return;
        }

        if (verbose) {
            std::cout << "Leyendo contenido de " << nombreArchivo << " desde el bloque inicial: " << std::endl;
        }

        // Recorremos todos los bloques del archivo usando la FAT
        while (bloqueActual != -1) {
            std::cout << "Leyendo bloque " << bloqueActual << ": ";
            for (int i = 0; i < TAM_BLOQUE; ++i) {
                std::cout << unidad[bloqueActual].marco[i];  // Mostramos cada byte del bloque
            }
            std::cout << std::endl;
            bloqueActual = tablaBloques[bloqueActual];  // Nos movemos al siguiente bloque en la FAT
        }

        std::cout << "Lectura completada para el archivo: " << nombreArchivo << std::endl;
    } else {
        if (verbose) {
            std::cout << "Error: Archivo '" << nombreArchivo << "' no encontrado." << std::endl;
        }
    }
}



void SistemaArchivosFAT::escribir(const std::string& nombreArchivo, std::vector<char>& datos, bool verbose) {
    int posicion = encontrarArchivo(nombreArchivo);
    int primerBloque = -1;  // Para guardar el primer bloque asignado
    int bloqueActual = -1;  // Para el bloque en el que estamos escribiendo
    int bloqueAnterior = -1; // Para enlazar el bloque anterior

    for (int j = 0; j < TAM_UNIDAD / TAM_BLOQUE && !datos.empty(); ++j) {
        if (unidad[j].marco[0] == '\0') {  // Encontramos un bloque vacío
            if (primerBloque == -1) {
                primerBloque = j;  // Este será el primer bloque del archivo
            }

            // Si hay un bloque anterior, enlazamos el bloque actual al anterior
            if (bloqueAnterior != -1) {
                tablaBloques[bloqueAnterior] = j;
            }

            bloqueActual = j;  // Actualizamos el bloque actual
            bloqueAnterior = j;  // Guardamos el bloque actual como el anterior para el siguiente enlace

            // Escribimos los datos en el bloque actual
            for (int i = 0; i < TAM_BLOQUE && !datos.empty(); ++i) {
                unidad[j].marco[i] = datos[0];
                datos.erase(datos.begin());  // Eliminamos el dato ya escrito
            }

            // Si no quedan más datos, marcamos el final del archivo
            if (datos.empty()) {
                tablaBloques[bloqueActual] = -1;  // Este es el último bloque
            }
        }
    }

    // Corregido: Asegúrate de que el bloque de inicio se actualiza correctamente
    if (directorio[posicion].bloqueInicio == -1) {
        directorio[posicion].bloqueInicio = primerBloque;  // IMPORTANTE: Asignamos el bloque de inicio
    }

    // Actualizar el bloque final siempre
    directorio[posicion].bloqueFin = bloqueActual;

    if (verbose) {
        std::cout << "Datos escritos en el archivo '" << nombreArchivo << "' correctamente." << std::endl;
    }
}



void SistemaArchivosFAT::imprimir() {
    std::cout << "Tabla de asignación de bloques (FAT):" << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << "Bloque " << i << ": " << tablaBloques[i] << std::endl;
    }

    std::cout << "\nContenido de los bloques:" << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << "Bloque " << i << ": ";
        for (int j = 0; j < 8; ++j) {
            if (unidad[i].marco[j] != '\0') {
                std::cout << unidad[i].marco[j] << " ";
            }
        }
        std::cout << std::endl;
    }
}

// verificar despues si la funcionalidad se deja o no, podria ser esta la idea de estos metodos
void SistemaArchivosFAT::buscar(const std::string& nombreArchivo, bool verbose) {
  int posicion = encontrarArchivo(nombreArchivo);

  if (posicion != -1) {
    if (verbose) {
      std::cout << "Archivo encontrado: " << directorio[posicion].nombre << std::endl;
      std::cout << "Bloque de inicio: " << directorio[posicion].bloqueInicio << std::endl;
      std::cout << "Bloque final: " << directorio[posicion].bloqueFin << std::endl;
      std::cout << "Estado: " << (directorio[posicion].abierto ? "Abierto" : "Cerrado") << std::endl;
    }
  } else {
    if (verbose) {
      std::cout << "Error: Archivo '" << nombreArchivo << "' no encontrado." << std::endl;
    }
  }
}


void SistemaArchivosFAT::borrar(const std::string& nombreArchivo, bool verbose) {
  int siguienteBloque = 0;
  int bloqueInicio = 0;

  for (size_t i = 0; i < cantidadDirectorios; i++) {
    if (directorio[i].nombre == nombreArchivo) {
      bloqueInicio = directorio[i].bloqueInicio;

      while (bloqueInicio != -1) {
        siguienteBloque = tablaBloques[bloqueInicio];
        tablaBloques[bloqueInicio] = -1;
        bloqueInicio = siguienteBloque;
      }

      directorio[i].nombre.clear();
      directorio[i].bloqueInicio = -1;

      if (verbose) {
        std::cout << "Archivo '" << nombreArchivo << "' borrado exitosamente." << std::endl;
      }
      return;
    }
  }

  if (verbose) {
    std::cout << "Error: Archivo '" << nombreArchivo << "' no encontrado." << std::endl;
  }
}
// void SistemaArchivosFAT::adjuntar(const std::string& nombreArchivo, std::vector<char>& datos, bool verbose) {
//     int posicionOriginal = encontrarArchivo(nombreArchivo);

//     if (posicionOriginal == -1) {
//         if (verbose) {
//             std::cout << "Error: Archivo '" << nombreArchivo << "' no encontrado." << std::endl;
//         }
//         return;
//     }

//     int bloqueActual = directorio[posicionOriginal].bloqueFin;  // Comenzamos desde el bloque final actual

//     if (bloqueActual == -1) {
//         // El archivo no tiene bloques, necesitamos asignar un bloque inicial
//         std::cout << "El archivo no tiene bloques asignados, asignando bloque inicial." << std::endl;
//         escribir(nombreArchivo, datos, verbose);  // Si no tiene bloques, simplemente lo escribimos
//         return;
//     }

//     std::cout << "Adjuntando datos al archivo: " << nombreArchivo << std::endl;

//     // Continuamos asignando bloques para los datos adicionales
//     while (!datos.empty()) {
//         // Buscamos el siguiente bloque vacío
//         int bloqueAsignado = -1;
//         for (int j = 0; j < TAM_UNIDAD / TAM_BLOQUE; ++j) {
//             if (unidad[j].marco[0] == '\0') {  // Encontramos un bloque vacío
//                 bloqueAsignado = j;
//                 break;
//             }
//         }

//         if (bloqueAsignado == -1) {
//             if (verbose) {
//                 std::cout << "Error: No hay bloques disponibles para adjuntar." << std::endl;
//             }
//             return;  // No hay más espacio para adjuntar
//         }

//         // Enlazamos el bloque actual con el nuevo bloque
//         tablaBloques[bloqueActual] = bloqueAsignado;
//         bloqueActual = bloqueAsignado;  // Actualizamos el último bloque asignado

//         std::cout << "Datos escritos en el bloque " << bloqueAsignado << std::endl;

//         // Escribimos los datos en el nuevo bloque
//         for (int i = 0; i < TAM_BLOQUE && !datos.empty(); ++i) {
//             unidad[bloqueAsignado].marco[i] = datos[0];
//             datos.erase(datos.begin());
//         }

//         // Marcamos el final del bloque como -1 en la FAT si no hay más datos
//         if (datos.empty()) {
//             tablaBloques[bloqueActual] = -1;
//         }
//     }

//     // Actualizamos el bloque final del archivo en el directorio
//     directorio[posicionOriginal].bloqueFin = bloqueActual;

//     std::cout << "Datos adjuntados completados para el archivo: " << nombreArchivo << std::endl;

//     if (verbose) {
//         std::cout << "Datos adjuntados al archivo '" << nombreArchivo << "' correctamente." << std::endl;
//     }
// }
void SistemaArchivosFAT::adjuntar(const std::string& nombreArchivo, std::vector<char>& datos, bool verbose) {
    int posicionOriginal = encontrarArchivo(nombreArchivo);

    if (posicionOriginal == -1) {
        if (verbose) {
            std::cout << "Error: Archivo '" << nombreArchivo << "' no encontrado." << std::endl;
        }
        return;
    }

    int bloqueActual = directorio[posicionOriginal].bloqueFin;  // Comenzamos desde el bloque final actual

    // Si el archivo no tiene bloques asignados, debemos crear el primero
    if (bloqueActual == -1) {
        escribir(nombreArchivo, datos, verbose);  // Si no tiene bloques, simplemente lo escribimos
        return;
    }

    std::cout << "Adjuntando datos al archivo: " << nombreArchivo << std::endl;

    // Continuamos asignando bloques para los datos adicionales
    while (!datos.empty()) {
        // Buscamos el siguiente bloque vacío
        int bloqueAsignado = -1;
        for (int j = 0; j < TAM_UNIDAD / TAM_BLOQUE; ++j) {
            if (unidad[j].marco[0] == '\0') {  // Encontramos un bloque vacío
                bloqueAsignado = j;
                break;
            }
        }

        if (bloqueAsignado == -1) {
            if (verbose) {
                std::cout << "Error: No hay bloques disponibles para adjuntar." << std::endl;
            }
            return;  // No hay más espacio para adjuntar
        }

        // Enlazamos el bloque actual con el nuevo bloque
        tablaBloques[bloqueActual] = bloqueAsignado;
        bloqueActual = bloqueAsignado;  // Actualizamos el último bloque asignado

        std::cout << "Datos escritos en el bloque " << bloqueAsignado << std::endl;

        // Escribimos los datos en el nuevo bloque
        for (int i = 0; i < TAM_BLOQUE && !datos.empty(); ++i) {
            unidad[bloqueAsignado].marco[i] = datos[0];
            datos.erase(datos.begin());
        }

        // Marcamos el final del bloque como -1 en la FAT si no hay más datos
        if (datos.empty()) {
            tablaBloques[bloqueActual] = -1;
        }
    }

    // Actualizamos el bloque final del archivo en el directorio
    directorio[posicionOriginal].bloqueFin = bloqueActual;

    std::cout << "Datos adjuntados completados para el archivo: " << nombreArchivo << std::endl;

    if (verbose) {
        std::cout << "Datos adjuntados al archivo '" << nombreArchivo << "' correctamente." << std::endl;
    }
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

void SistemaArchivosFAT::renombrar(const std::string& nombreArchivo, const std::string& nuevoNombre, bool verbose) {
  int posicionOriginal = encontrarArchivo(nombreArchivo);

  if (posicionOriginal == -1) {
    if (verbose) {
      std::cout << "Error: Archivo '" << nombreArchivo << "' no encontrado." << std::endl;
    }
    return;
  }

  int posicionNuevoNombre = encontrarArchivo(nuevoNombre);
  if (posicionNuevoNombre != -1) {
    if (verbose) {
      std::cout << "Error: El archivo '" << nuevoNombre << "' ya existe." << std::endl;
    }
    return;
  }

  directorio[posicionOriginal].nombre = nuevoNombre;
  
  if (verbose) {
    std::cout << "Archivo '" << nombreArchivo << "' ha sido renombrado a '" << nuevoNombre << "' correctamente." << std::endl;
  }
}

void SistemaArchivosFAT::listar() {
  for (size_t i = 0; i < cantidadDirectorios; i++) {
 
      std::cout << "Contenido de la dirección: " << i << " | "
                << "Nombre del archivo: " << directorio[i].nombre
                << " | Bloque de inicio: " << directorio[i].bloqueInicio
                << " | Bloque final: " << directorio[i].bloqueFin
                << " | Estado: " << (directorio[i].abierto ? " Abierto" : " Cerrado")
                << std::endl;
  }
}

int SistemaArchivosFAT::encontrarArchivo(const std::string& nombreArchivo, bool verbose) {
  for (size_t i = 0; i < cantidadDirectorios; i++) {
    if (directorio[i].nombre == nombreArchivo) {
      if (verbose) {
        std::cout << "Archivo '" << nombreArchivo << "' encontrado." << std::endl;
      }
      return i;  // Retorna la posición en el directorio si se encuentra
    }
  }

  if (verbose) {
    std::cout << "Error: Archivo '" << nombreArchivo << "' no encontrado." << std::endl;
  }
  return -1;  // Retorna -1 si no se encuentra el archivo
}
