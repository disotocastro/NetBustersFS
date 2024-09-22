#ifndef SISTEMA_ARCHIVOS_FAT_HPP
#define SISTEMA_ARCHIVOS_FAT_HPP

#include <iostream>
#include <string>
#include <vector>

#define TAM_BLOQUE 256
#define TAM_UNIDAD 65536
#define TAM_TABLA 256

/**
 * @struct Archivo
 * @brief Estructura que representa un archivo en el sistema de archivos FAT.
 *
 * Esta estructura contiene los metadatos de un archivo, incluyendo su nombre,
 * permisos, usuario propietario, y otros atributos necesarios para gestionar su
 * estado y ubicación en el sistema.
 */
struct Archivo {
  ///< Nombre del archivo.
  std::string nombre;
  ///< Permisos del archivo (e.g., "r--", "rw-").
  std::string permisos;
  ///< Usuario propietario del archivo.
  std::string usuario;
  ///< Indicador de si el archivo está actualmente abierto.
  bool abierto;
  ///< Índice del bloque de inicio del archivo en la tabla FAT.
  int bloqueInicio;
  ///< Índice del bloque final del archivo en la tabla FAT.
  int bloqueFin;
  ///< ID del proceso asociado que tiene el archivo abierto (si aplica).
  int proceso;
  ///< Posición actual del cursor para operaciones de lectura/escritura.
  int cursor;
  ///< tamaño del archivo en bytes.
  int tamaño;

  /**
   * @brief Constructor por defecto de la estructura Archivo.
   *
   * Inicializa los valores predeterminados de los atributos del archivo.
   */
  Archivo()
      : nombre(""),
        bloqueInicio(-1),
        bloqueFin(-1),
        abierto(false),
        permisos("r--"),
        usuario(""),
        proceso(-1),
        cursor(0) {}
};

struct Marco {
  char marco[TAM_BLOQUE];
};

/**
 * @class SistemaArchivosFAT
 * @brief Clase que simula un sistema de archivos basado en FAT (File Allocation
 * Table).
 *
 * Esta clase implementa un sistema de archivos simple utilizando una tabla FAT
 * para gestionar archivos. Permite crear, abrir, cerrar, leer, escribir,
 * renombrar y borrar archivos, así como realizar búsquedas y gestionar el
 * directorio de archivos.
 */
class SistemaArchivosFAT {
 private:
  ///< Cantidad de directorios en el sistema.
  int cantidadDirectorios;

  ///< Tabla de bloques FAT, donde cada bloque tiene 8 caracteres.
  int tablaBloques[TAM_TABLA];

  ///< Arreglo de marcos (frames) que representa la unidad de almacenamiento.
  Marco unidad[TAM_TABLA];

  ///< Directorio de archivos del sistema.
  Archivo directorio[TAM_TABLA];

 public:
  /**
   * @brief Constructor de la clase SistemaArchivosFAT.
   * Inicializa el sistema de archivos y sus componentes.
   */
  SistemaArchivosFAT();

  /**
   * @brief Abre un archivo y coloca el cursor al inicio.
   * @param nombreArchivo Nombre del archivo a abrir.
   * @return True si logra abrir el archivo, False si no lo logra.
   */
  bool abrir(const std::string& nombreArchivo);

  /**
   * @brief Cierra un archivo previamente abierto.
   * @param nombreArchivo Nombre del archivo a cerrar.
   * @return True si logra cerrar el archivo, False si no lo logra.
   */
  bool cerrar(const std::string& nombreArchivo);

  /**
   * @brief Crea un archivo nuevo en el directorio.
   * @param nombreArchivo Nombre del archivo a crear.
   * @return True si logra crear el archivo, False si no lo logra.
   */
  bool crear(const std::string& nombreArchivo);

  /**
   * @brief Lee n cantidad de caracteres desde la posición actual del cursor en
   * un archivo.
   * @param nombreArchivo Nombre del archivo desde el que se va a leer.
   * @return los datos que se leyeron
   */
  std::string leer(const std::string& nombreArchivo, int cantidadLeer);

  /**
   * @brief Busca un archivo en el directorio.
   * @param nombreArchivo Nombre del archivo a buscar.
   * @return True si logra encontrar el archivo, False si no lo logra.
   */
  int buscar(const std::string& nombreArchivo);

  /**
   * @brief Borra un archivo del directorio y libera sus bloques en la tabla
   * FAT.
   * @param nombreArchivo Nombre del archivo a borrar.
   * @return True si logra borrar el archivo, False si no lo logra.
   */
  bool borrar(const std::string& nombreArchivo);

  /**
   * @brief Adjunta (escribe al final) datos en un archivo existente.
   * @param nombreArchivo Nombre del archivo.
   * @param datos Datos a adjuntar.
   * @return True si logra adjuntar al archivo, False si no lo logra.
   */
  bool adjuntar(const std::string& nombreArchivo, std::vector<char>& datos);

  /**
   * @brief Renombra un archivo existente.
   * @param nombreArchivo Nombre actual del archivo.
   * @param nuevoNombre Nuevo nombre para el archivo.
   */
  bool renombrar(const std::string& nombreArchivo,
                 const std::string& nuevoNombre);

  /**
   * @brief Lista todos los archivos presentes en el directorio.
   */
  void listar();
  /**
   * @brief Escribe datos en el archivo desde la posición actual del cursor.
   * 
   * Este método permite escribir datos en el archivo especificado comenzando desde la posición actual del cursor. 
   * Si el archivo no existe, se manejará el error correspondiente.
   *
   * @param nombreArchivo Nombre del archivo en el que se van a escribir los datos.
   * @param datos Cadena de caracteres que contiene los datos a escribir en el archivo.
   */
  void escribir(const std::string& nombreArchivo, std::string datos);

  /**
   * @brief Sincroniza el cursor de un archivo a una posición específica.
   * 
   * Este método permite actualizar la posición del cursor para un archivo específico. 
   * Es útil para asegurar que el cursor se encuentre en la posición correcta antes de realizar operaciones de lectura o escritura.
   *
   * @param archivo Índice del archivo en el sistema de archivos.
   * @param posicion Nueva posición a la que se desea mover el cursor.
   */
  void sincronizarCursor(int archivo, const int posicion);

  /**
   * @brief Imprime el contenido del sistema de archivos.
   * 
   * Este método se encarga de mostrar la información de todos los archivos almacenados en el sistema de archivos, 
   * así como sus metadatos relevantes, como nombres y posiciones de bloques.
   */
  void imprimir();

  /**
   * @brief Cambia la posición del cursor en un archivo.
   * 
   * Este método es utilizado para pruebas, permitiendo mover el cursor a una posición específica dentro del archivo 
   * indicado. Es útil para verificar la correcta funcionalidad de las operaciones de lectura y escritura.
   *
   * @param nombreArchivo Nombre del archivo cuyo cursor se desea mover.
   * @param pos Nueva posición del cursor dentro del archivo.
   */
  void cambiarCursor(const std::string& nombreArchivo, int pos);
};

#endif  // SISTEMA_ARCHIVOS_FAT_HPP
