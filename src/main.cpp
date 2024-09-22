#include <iostream>

#include "SistemaArchivosFAT.hpp"

int main() {
  SistemaArchivosFAT fs;

  // Crear archivo y escribir datos
  fs.crear("file1.txt");
  fs.escribir("file1.txt", "En la actualidad, el crecimiento iento exponencial de datos");
  fs.escribir("file1.txt", "En la actualidad, el crecimiento iento exponencial de datos");
  // fs.escribir("file1.txt", " feliz navidad agregare");
  // fs.imprimir();
  // fs.crear("file4.txt");
  // fs.crear("file2.txt");
  // fs.crear("file3.txt");

  // fs.escribir("file4.txt", "Juan Mata, holamundo");
  // fs.escribir("file2.txt", "Sebastian Ruiz, holamundo2");
  // fs.escribir("file3.txt", "Maria Vargas, holamundo3");
  fs.imprimir();

  std::cout << std::endl << "-->" <<fs.leer("file1.txt",500) << std::endl << std::endl;


  return 0;
}