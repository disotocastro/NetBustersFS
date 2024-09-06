#ifndef SISTEMA_ARCHIVOS_FAT_HPP
#define SISTEMA_ARCHIVOS_FAT_HPP

#include <string>
#include <vector>

// Definiciones básicas
const int TAM_BLOQUE = 8;  // Tamaño de cada bloque
const int TAM_UNIDAD = 4096;  // Tamaño de la unidad (arreglo de 4096 chars)
const int TAM_TABLA = 1 << TAM_BLOQUE; // tamaño de FAT es 2^8
// Estructura para representar un archivo en el sistema
struct Archivo {
  std::string nombre;
  int bloqueInicio;  // Bloque donde comienza el archivo
  //int tamaño;  // Tamaño del archivo en bloques, no se si esto realmente es asi, quiza despues se cambie
  //inicializar el archivo
  Archivo() : nombre(""), bloqueInicio(-1) {}
};

struct Marcos{
  char marco[TAM_BLOQUE]; // Cada frame tiene 8 bytes
};
// Clase SistemaArchivosFAT
class SistemaArchivosFAT {
private:
  Marcos unidad[TAM_UNIDAD/TAM_BLOQUE]; // Arreglo de frames 
  int tablaBloques[TAM_TABLA];  // Tabla de bloques de 8 chars cada uno
  std::vector<Archivo> directorio;  // Directorio de archivos

public:
  SistemaArchivosFAT();

  // Métodos del sistema de archivos
  void abrir(const std::string& nombreArchivo);
  void cerrar(const std::string& nombreArchivo);
  void crear(const std::string& nombreArchivo, std::vector<char>& datos);
  void leer(const std::string& nombreArchivo);
  void escribir(const std::string& nombreArchivo, const std::string& datos);
  void buscar(const std::string& nombreArchivo);
  void borrar(const std::string& nombreArchivo);
  void adjuntar(const std::string& nombreArchivo, const std::string& datos);
  void renombrar(const std::string& nombreArchivo, const std::string& nuevoNombre);
  void listar();

private:
  int encontrarArchivo(const std::string& nombreArchivo);  // Método auxiliar para buscar archivos
  int asignarBloques(int tamaño);  // Método auxiliar para asignar bloques
  void liberarBloques(int bloqueInicio);  // Método auxiliar para liberar bloques
};

#endif // SISTEMA_ARCHIVOS_FAT_HPP
