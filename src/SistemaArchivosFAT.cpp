#include "SistemaArchivosFAT.hpp"

#include <cstring>
#include <iostream>

// Constructor
SistemaArchivosFAT::SistemaArchivosFAT() {
  // Implementar
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

  directorio.resize(5);  // Se crea un directorio con tamaño fijo de 5
}

void SistemaArchivosFAT::abrir(const std::string& nombreArchivo) {
  // Implementar
}

void SistemaArchivosFAT::cerrar(const std::string& nombreArchivo) {
  // Implementar
}

void SistemaArchivosFAT::crear(const std::string& nombreArchivo,
                               std::vector<char>& datos) {
  int posAnterior =
      -1;  // Iniciar con -1 para indicar que no hay posición anterior

  for (size_t i = 0; i < directorio.size(); ++i) {
    // Busca espacio vacío en el directorio
    if (directorio[i].nombre.empty()) {
      directorio[i].nombre = nombreArchivo;  // Asigna nombre en el directorio
      directorio[i].bloqueInicio = -1;       // Inicializa el bloque de inicio

      // Ingresar datos a la unidad
      for (int j = 0; j < TAM_UNIDAD / TAM_BLOQUE && !datos.empty(); ++j) {
        // Si se encuentra un marco vacío en la unidad
        if (unidad[j].marco[0] == '\0') {
          if (directorio[i].bloqueInicio == -1) {
            directorio[i].bloqueInicio =
                j;  // Asigna el primer bloque al inicio del archivo
          } else {
            tablaBloques[posAnterior] =
                j;  // Actualiza FAT con la posición anterior
          }
          posAnterior = j;

          // Guardar los datos en el frame
          for (int k = 0; k < TAM_BLOQUE && !datos.empty(); ++k) {
            unidad[j].marco[k] =
                datos[0];  // Asigna el char en el espacio vacío del frame
            datos.erase(datos.begin());  // Borra el primer elemento del vector
          }
        }
      }
      break;  // Sale del bucle después de encontrar un espacio vacío y asignar
              // los datos
    }
  }
}

void SistemaArchivosFAT::leer(const std::string& nombreArchivo) {
  // Implementar
}

void SistemaArchivosFAT::escribir(const std::string& nombreArchivo,
                                  const std::string& datos) {
  // Implementar
}

void SistemaArchivosFAT::buscar(const std::string& nombreArchivo) {
  // Implementar
}

void SistemaArchivosFAT::borrar(const std::string& nombreArchivo) {
  int siguienteBloque = 0;
  int bloqueInicio = 0;

  for (size_t i = 0; i < directorio.size(); i++) {
    // Si existe el archivo en el directorio
    if (directorio[i].nombre == nombreArchivo) {
      bloqueInicio = directorio[i].bloqueInicio;

      // Liberar los bloques
      while (bloqueInicio != -1) {
        // Se incia el borrado en elprimer bloque de la tabla
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
                                  const std::string& datos) {
  // Implementar
}

void SistemaArchivosFAT::renombrar(const std::string& nombreArchivo,
                                   const std::string& nuevoNombre) {
  // Implementar
}

void SistemaArchivosFAT::listar() {
  for (size_t i = 0; i < directorio.size(); i++) {
    if (!directorio[i].nombre.empty()) {
      std::cout << "Contenido de la dirección: " << i << " | "
                << "Nombre del archivo: " << directorio[i].nombre
                << " | Bloque de inicio: " << directorio[i].bloqueInicio
                << std::endl;
    } else {
      std::cout << "Directorio vacío en la posición: " << i << std::endl;
    }
  }
}

int SistemaArchivosFAT::encontrarArchivo(const std::string& nombreArchivo) {
  // Implementar
}

int SistemaArchivosFAT::asignarBloques(int tamaño) {
  // Implementar
}

void SistemaArchivosFAT::liberarBloques(int bloqueInicio) {
  // Implementar
}
