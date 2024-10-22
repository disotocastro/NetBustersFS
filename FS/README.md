# NetBustersFS

## Sistema de Archivos FAT

### Requisitos del Sistema de Archivos

El sistema de archivos debe cumplir con los siguientes requisitos:

1. **Atributos**:
    - **Unidad**: Un arreglo de 4096 chars que simula el almacenamiento de la unidad.
    - **Directorio**: Una lista que contiene la información de los archivos almacenados en la unidad.
    - **Tabla de bloques**: Una tabla que divide la unidad en bloques de 8 chars cada uno, similar al concepto de la FAT (File Allocation Table).

2. **Métodos del Sistema de Archivos**:
    Implementar los siguientes métodos para gestionar los archivos y el espacio en disco:

    - **abrir**: Permite abrir un archivo en el sistema.
    - **cerrar**: Cierra un archivo previamente abierto.
    - **crear**: Crea un nuevo archivo en la unidad con un nombre y un tamaño especificado.
    - **leer**: Lee los datos almacenados en un archivo.
    - **escribir**: Escribe datos en un archivo existente.
    - **buscar**: Busca un archivo por su nombre.
    - **borrar**: Elimina un archivo del sistema.
    - **adjuntar**: Adjunta nuevos datos a un archivo existente, extendiendo su tamaño.
    - **renombrar**: Cambia el nombre de un archivo.
    - **listar**: Muestra todos los archivos presentes en el sistema.
