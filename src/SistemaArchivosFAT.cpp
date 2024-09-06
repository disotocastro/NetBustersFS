#include "SistemaArchivosFAT.hpp"
#include <iostream>
#include <cstring>

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
            unidad[i].marco[j] = '\0';  // se inicializan todos los bytes de cada frame nulo
        }
    }
}


void SistemaArchivosFAT::abrir(const std::string& nombreArchivo) {
    // Implementar
}

void SistemaArchivosFAT::cerrar(const std::string& nombreArchivo) {
    // Implementar
}

void SistemaArchivosFAT::crear(const std::string& nombreArchivo, std::vector<char>& datos) {
    // Implementar
    int posAnterior = 0; // auxiliar para conocer cual era la posicion donde se le asignara la siguiente en el fat
    for (int i = 0; i < directorio.size(); ++i) {
        // busca espacio vacio en el directorio
        if (directorio[i].nombre.empty()) {
            directorio[i].nombre = nombreArchivo; // asignar nombre en el directorio

            // ingresar datos a la unidad
            for (int i = 0; i < TAM_UNIDAD / TAM_BLOQUE; ++i) {
                // si se encuentra un marco vacio en la unidad
                if ((unidad[i].marco[0] == '\0')&& (!datos.empty())){
                    // asignar al el inicio en el fat
                    if  (directorio[i].bloqueInicio == -1){
                        directorio[i].bloqueInicio = i;
                    } else {
                        // posiciones en el fat
                        if  (tablaBloques[posAnterior] == -1){ // esto siempre se deberia cumplir
                            tablaBloques[posAnterior] = i;
                        }
                    }
                    // guardar las posiciones anteriores
                    posAnterior = i;

                    // guardar los datos en el frame
                    for (int j = 0; j < TAM_BLOQUE; ++j) { 
                        unidad[i].marco[j] = datos[0]; // asigna el char en el espacio vacio del frame
                        datos.erase(datos.begin()); // borra el primer elemento del vector
                    }
                }
                
            }
        }
    }

}

void SistemaArchivosFAT::leer(const std::string& nombreArchivo) {
    // Implementar
}

void SistemaArchivosFAT::escribir(const std::string& nombreArchivo, const std::string& datos) {
    // Implementar

}

void SistemaArchivosFAT::buscar(const std::string& nombreArchivo) {
    // Implementar
}

void SistemaArchivosFAT::borrar(const std::string& nombreArchivo) {
    // Implementar
}

void SistemaArchivosFAT::adjuntar(const std::string& nombreArchivo, const std::string& datos) {
    // Implementar
}

void SistemaArchivosFAT::renombrar(const std::string& nombreArchivo, const std::string& nuevoNombre) {
    // Implementar
}

void SistemaArchivosFAT::listar() {
    // Implementar
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
