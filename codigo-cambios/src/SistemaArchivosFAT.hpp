#ifndef SISTEMA_ARCHIVOS_FAT_HPP
#define SISTEMA_ARCHIVOS_FAT_HPP

#include <string>
#include <vector>

// Definiciones básicas
const int TAM_BLOQUE = 8;     // Tamaño de cada bloque
const int TAM_UNIDAD = 4096;  // Tamaño de la unidad (arreglo de 4096 chars)
const int TAM_TABLA = 1 << TAM_BLOQUE;  // tamaño de FAT es 2^8

// Estructura para representar un archivo en el sistema
struct Archivo {
  std::string nombre;
  int bloqueInicio;  // Bloque donde comienza el archivo:vector<char> datos1 = {'H', 'o', 'l', 'a', 'M', 'u', 'n', 'd', 'o'};
  int bloqueFin;
  // int tamaño;  // Tamaño del archivo en bloques, no se si esto realmente es
  // asi, quiza despues se cambie inicializar el archivo
  bool abierto;  // Nueva bandera para indicar si el archivo está abierto
  std::string permisos;
  std::string usuario;
  int proceso;
  int cursor; // para saber de donde desea empezar a leer
  Archivo() : nombre(""), bloqueInicio(-1), bloqueFin(-1), abierto(false)
    , permisos ("r--"), usuario(""), proceso(-1), cursor(-1){}
};

struct Marcos {
  char marco[TAM_BLOQUE];  // Cada frame tiene 8 bytes
};

// Clase SistemaArchivosFAT
class SistemaArchivosFAT {
 private:
  int cantidadDirectorios;
  Marcos unidad[TAM_UNIDAD / TAM_BLOQUE];  // Arreglo de frames
  int tablaBloques[TAM_TABLA];      // Tabla de bloques de 8 chars cada uno
  //std::vector<Archivo> directorio;  // Directorio de archivos
  Archivo directorio [TAM_UNIDAD];

 public:
  SistemaArchivosFAT();

  // Métodos del sistema de archivos
  void abrir(const std::string& nombreArchivo, bool verbose);
  void cerrar(const std::string& nombreArchivo);
  void crear(const std::string& nombreArchivo);
  void crearConArchivos(const std::string& nombreArchivo
                          , std::vector<char>& datos);
  void leer(const std::string& nombreArchivo);
  void buscar(const std::string& nombreArchivo);
  void borrar(const std::string& nombreArchivo);
  void adjuntar(const std::string& nombreArchivo, std::vector<char>& datos);
  void renombrar(const std::string& nombreArchivo,
                 const std::string& nuevoNombre);
  void listar();
 void escribir(const std::string& nombreArchivo, std::vector<char>& datos);
 void imprimir();
 private:
  // Método auxiliar para buscar archivos
  int encontrarArchivo(const std::string& nombreArchivo);
  // Método auxiliar para asignar bloques
  int asignarBloques(int tamano);
  // Método auxiliar para liberar bloques
  void liberarBloques(int bloqueInicio);
  // escribir de adjuntar
  void escribirAdjuntando(size_t marco, std::vector<char>& datos);

 
};

#endif  // SISTEMA_ARCHIVOS_FAT_HPP
