#include <iostream>

#include "SistemaArchivosFAT.hpp"

int main() {
  SistemaArchivosFAT fs;

  // Crear archivo y escribir datos
  fs.crear("user1.txt");
  fs.crear("user2.txt");
  fs.crear("user3.txt");
  fs.crear("user4.txt");
  fs.crear("user5.txt");
  fs.crear("user6.txt");
  fs.crear("user7.txt");
  fs.crear("user8.txt");
  fs.crear("user9.txt");
  fs.crear("user10.txt");
  /// user id, name, pas, admin,state,f1,f2,f3,s1,s2,s3,s4
  fs.escribir("user1.txt", "juanmata43, Juan Mata, cookie33, 0, 1, 1, 0, 0, 1, 1, 0, 0");
  fs.escribir("user2.txt", "mariavar1, Maria Vargas, abcde12, 0, 1, 1, 0, 0, 1, 1, 0, 0");
  fs.escribir("user3.txt", "willi777, William Morales, fghij34, 1, 1, 1, 1, 1, 1, 1, 1, 1");
  fs.escribir("user4.txt", "diegoSo65, Diego Soto, klmno56, 1, 1, 1, 1, 1, 1, 1, 1, 1");
  fs.escribir("user5.txt", "andymurr55, Andres Murillo, pqrst78, 1, 1, 1, 1, 1, 1, 1, 1, 1");
  fs.escribir("user6.txt", "tatspar44, Tatiana Paramo, uvwxy90, 1, 1, 1, 1, 1, 1, 1, 1, 1");
  fs.escribir("user7.txt", "morasebas47, Sebastian Mora, mnopq11, 0, 1, 1, 1, 0, 0, 0, 0, 1");
  fs.escribir("user8.txt", "josandrade1, Jose Andrade, rstuv22, 0, 1, 1, 0, 1, 0, 0, 1, 0");
  fs.escribir("user9.txt", "valenegrc89, Valeria Blanco, abcdz44, 0, 1, 1, 0, 0, 1, 1, 0, 0");
  fs.escribir("user10.txt", "martinrod6, Martina Rodriguez, efghi55, 0, 1, 1, 0, 0, 1, 0, 1, 0");

  fs.imprimir();

  std::cout << std::endl << "-->" <<fs.leer("user1.txt",500) << std::endl << std::endl;
  std::cout << std::endl << "-->" <<fs.leer("user7.txt",65) << std::endl << std::endl;

  return 0;
  
}