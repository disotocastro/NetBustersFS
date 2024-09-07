#include <iostream>

#include "SistemaArchivosFAT.hpp"

int main() {
  SistemaArchivosFAT fs;
  std::vector<char> datos1 = {'H', 'o', 'l', 'a', 'M', 'u', 'n', 'd', 'o'};
  fs.crear("file1.txt", datos1);

  std::vector<char> datos2 = {'H', 'o', 'l', 'a', 'M', 'u', '1', '1', '0'};
  fs.crear("file2.txt", datos2);

  fs.listar();

  fs.borrar("file2.txt");
  fs.borrar("file1.txt");

  fs.listar();

  return 0;
}
