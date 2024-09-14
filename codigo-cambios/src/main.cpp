// #include <iostream>

// #include "SistemaArchivosFAT.hpp"

// int main() {
//   SistemaArchivosFAT fs;
//   std::vector<char> datos1 = {'H', 'o', 'l', 'a', 'M', 'u', 'n', 'd', 'o'};
//   fs.crear("file1.txt", datos1);

//   std::vector<char> datos2 = {'H', 'o', 'l', 'a', 'M', 'u', '1', '1', '0'};
//   fs.crear("file2.txt", datos2);

//   fs.listar();

//   std::vector<char> datos3 = {'H', 'o', 'l', 'a', 'M', 'u', '2', '2', '0'};
//   fs.adjuntar("file2.txt", datos3);

//   fs.leer("file2.txt");

//   std::vector<char> datos4 = {'H', 'o', 'l', 'a', 'M', 'u', '3', '3', '0'};
//   fs.crear("file3.txt", datos4);


//   fs.listar();

//   fs.borrar("file2.txt");
//   fs.borrar("file1.txt");

//   fs.listar();

//   return 0;
// }

#include <iostream>
#include "SistemaArchivosFAT.hpp"

int main() {
  SistemaArchivosFAT fs;
  
  // Crear algunos archivos
  std::vector<char> datos1 = {'H', 'o', 'l', 'a', 'M', 'u', 'n', 'd', 'o'};
  fs.crear("file1.txt");
  fs.escribir("file1.txt", datos1);
  std::vector<char> datos2 = {'T', 'o'};
  fs.adjuntar("file1.txt", datos2);
  fs.abrir("file1.txt", 1);
  fs.leer("file1.txt");
  fs.listar();
  fs.imprimir();


  // std::vector<char> datos3= {'H', 'o', 'l', 'a', 'M', 'u', '1', '1', '0'};
  // fs.crear("file2.txt");
  // fs.escribir("file2.txt", datos2);
  // fs.adjuntar("file2.txt", datos2);
  // fs.listar();
  // std::vector<char> datos4 = {'K', 'A', 'K', 'A', 'K', 'A'};
  // fs.adjuntar("file2.txt", datos2);
  // fs.abrir("file1.txt", 1);
  // fs.buscar("file1.txt");

  // Listar para ver los archivos creados
  // fs.listar();

  // Probar el método abrir
  // std::cout << "\n--- Probando abrir ---\n";

  // fs.listar();
  // // Probar el método buscar para verificar si está abierto
  // std::cout << "\n--- Probando buscar (debería estar abierto) ---\n";

  // // Leer el contenido del archivo (debería permitir lectura)
  // std::cout << "\n--- Leyendo file1.txt ---\n";
  // fs.leer("file1.txt");

  // // Probar cerrar el archivo
  // std::cout << "\n--- Probando cerrar ---\n";
  // fs.cerrar("file1.txt");

  // // Buscar de nuevo para verificar si se cerró correctamente
  // std::cout << "\n--- Probando buscar (debería estar cerrado) ---\n";
  // fs.buscar("file1.txt");

  // // Intentar leer el archivo cerrado (debería fallar)
  // std::cout << "\n--- Intentando leer archivo cerrado ---\n";
  // fs.leer("file1.txt");


  // // Listar para ver el estado final
  // std::cout << "\n--- Estado final del directorio ---\n";
  // fs.listar();

 return 0;
}