# Tarea 3 -  Cliente-Servidor

Este proyecto implementa un sistema cliente-servidor en Linux utilizando sockets. El cliente puede realizar operaciones como la creación, guardado y eliminación de archivos, así como autenticarse con el servidor.

## Miembros del Equipo

- **William Morales**:  
  Este realiza la implementacion de la funcionalidad para crear y guardar archivos. Se aseguró de que el cliente pudiera enviar comandos al servidor para crear nuevos archivos y almacenar su contenido de manera correcta.

- **Diego Soto**:  
  Implementó la funcionalidad para eliminar archivos. Se encargó de que el cliente pudiera enviar una solicitud al servidor para eliminar archivos y que esta fuera procesada adecuadamente.

- **Tatiana Paramo**:  
  Trabajó en el proceso de guardado de archivos. Implementó el código que permite al cliente abrir un archivo localmente y enviar su contenido al servidor mediante el comando "guardar".

- **Andres Murillo**:  
  Implementó el sistema de autenticación. Se encargó de que el cliente pudiera enviar las credenciales de usuario al servidor, y que este último validara las credenciales, devolviendo una respuesta de éxito o fracaso.

## Progreso y Resultados

Se implemento todo, algunas cosas se trabajaron de forma grupal donde los cuatro participabamos.

---

## Compilar
Compilar el server:

```sh
g++ "Source Files/main.cpp" "Source Files/filesystem.cpp" -o server -I"Header Files"
./server 
```

Compilar el cliente:

```sh
g++ "Source Files/client.cpp" "Source Files/main.cpp" -o client -I"Header Files"
./client
```
