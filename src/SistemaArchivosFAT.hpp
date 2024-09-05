#ifndef SISTEMA_ARCHIVOS_FAT_HPP
#define SISTEMA_ARCHIVOS_FAT_HPP

#include <string>
#include <vector>

// Definiciones básicas
const int TAM_BLOQUE = 8;  // Tamaño de cada bloque
const int TAM_UNIDAD = 4096;  // Tamaño de la unidad (arreglo de 4096 chars)

// Estructura para representar un archivo en el sistema
struct Archivo {
  std::string nombre;
  int bloqueInicio;  // Bloque donde comienza el archivo
  int tamaño;  // Tamaño del archivo en bloques, no se si esto realmente es asi, quiza despues se cambie 
};

// Clase SistemaArchivosFAT
class SistemaArchivosFAT {
private:
  char unidad[TAM_UNIDAD];  // Unidad de almacenamiento
  int tablaBloques[TAM_UNIDAD / TAM_BLOQUE];  // Tabla de bloques de 8 chars cada uno
  std::vector<Archivo> directorio;  // Directorio de archivos

public:
  SistemaArchivosFAT();

  // Métodos del sistema de archivos
  void abrir(const std::string& nombreArchivo);
  void cerrar(const std::string& nombreArchivo);
  void crear(const std::string& nombreArchivo, int tamaño);
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
