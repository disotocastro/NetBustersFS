#include <iostream>

#include "SistemaArchivosFAT.hpp"

int main() {
  // Inicializar el sistema de archivos FAT

  SistemaArchivosFAT fs;
  std::vector<char> datos1 = {'H', 'o', 'l', 'a', 'M', 'u', 'n', 'd', 'o'};
  fs.crear("file1.txt", datos1);

  fs.listar();

  return 0;
}
