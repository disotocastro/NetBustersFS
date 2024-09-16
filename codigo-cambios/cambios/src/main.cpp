#include <iostream>
#include "SistemaArchivosFAT.hpp"

int main() {
  SistemaArchivosFAT fs;
  
  // Crear archivo sin datos (verbose activado)
  fs.crear("file1.txt", true);  // Creación del archivo sin datos
  
  // Crear archivo con datos desde el inicio (verbose activado)
  std::vector<char> datos2 = {'H', 'o', 'l', 'a', ' ', 'M', 'u', 'n', 'd', 'o'};
  fs.crear("file2.txt", datos2, true);  // Creación del archivo con datos
  
  // Adjuntar más datos al archivo file2.txt
  std::vector<char> datosAdicionales = {'!', '!', '!'};
  fs.adjuntar("file2.txt", datosAdicionales, true);  // Adjuntar datos al archivo existente
  
  // Abrir el archivo file2.txt para leerlo (verbose activado)
  fs.abrir("file2.txt", true);
  
  // Leer el contenido del archivo file2.txt
  fs.leer("file2.txt", true);
  
  // Listar todos los archivos creados
  fs.listar();
  
  // Imprimir la tabla de bloques y los frames de la unidad
  fs.imprimir();

  return 0;
}