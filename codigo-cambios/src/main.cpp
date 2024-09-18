#include <iostream>

#include "SistemaArchivosFAT.hpp"

int main() {
  SistemaArchivosFAT fs;

  // Crear archivo y escribir datos
  std::vector<char> datos1 = {'H', 'o', 'l', 'a', 'M', 'u', 'n', 'd', 'o'};
  fs.crear("file1.txt");
  fs.escribir("file1.txt", datos1);

  // Leer antes de adjuntar para verificar contenido inicial
  std::cout << "\n--- Contenido inicial de file1.txt ---\n";
  fs.abrir("file1.txt", 1);
  fs.leer("file1.txt");

  // Adjuntar nuevos datos
  std::vector<char> datosAdjuntados = {'!', '!', '!', ' ', 'E',
                                       'x', 't', 'r', 'a'};
  fs.adjuntar("file1.txt", datosAdjuntados);

  // Leer después de adjuntar para verificar que se lea todo correctamente
  std::cout << "\n--- Contenido después de adjuntar datos a file1.txt ---\n";
  fs.leer("file1.txt");

  // Probar con otro archivo
  std::vector<char> datos2 = {'D', 'a', 't', 'o', 's', ' ', 'i', 'n',
                              'i', 'c', 'i', 'a', 'l', 'e', 's'};
  fs.crear("file2.txt");
  fs.escribir("file2.txt", datos2);

  std::cout << "\n--- Contenido inicial de file2.txt ---\n";
  fs.abrir("file2.txt", 1);
  fs.leer("file2.txt");

  // Adjuntar nuevos datos
  std::vector<char> datosAdjuntados2 = {' ', 'a', 'd', 'j', 'u', 'n',
                                        't', 'a', 'd', 'o', 's'};
  fs.adjuntar("file2.txt", datosAdjuntados2);

  std::cout << "\n--- Contenido después de adjuntar datos a file2.txt ---\n";
  fs.leer("file2.txt");

  // Listar todos los archivos para verificar el estado
  std::cout << "\n--- Estado final del sistema de archivos ---\n";
  fs.listar();

  std::cout << "imprmir<111" << std::endl;
  fs.imprimir();

  return 0;
}