# NetBusters - Autenticador de Usuarios

Este proyecto es un sistema de autenticación de usuarios basado en un sistema de archivos personalizado que almacena datos como contraseñas, accesos a sensores, y permisos de administración.

## Requisitos

1. **Sistema Operativo**: Windows 10 o superior
2. **Compilador**: `g++` de MinGW (puedes descargar MinGW desde [aquí](https://sourceforge.net/projects/mingw/))
3. **CMake**: Opcional, si prefieres un sistema de compilación basado en CMake.

## Estructura del Proyecto

```txt
NetBusters/
│
├── Header Files/
│   ├── authenticator.h
│   ├── filesystem.h
│
├── Source Files/
│   ├── authenticator.cpp
│   ├── filesystem.cpp
│   ├── main.cpp
│
└── users/
    └── users_data.txt  # Aquí se almacenan los usuarios y sus datos
```

### Archivos importantes

- **authenticator.h/cpp**: Módulo que maneja la autenticación de usuarios.
- **filesystem.h/cpp**: Sistema de archivos para almacenar datos.
- **main.cpp**: Punto de entrada del programa.

## Cómo Compilar

### Paso 1: Instalar MinGW

1. Si no tienes MinGW instalado, descárgalo de [SourceForge](https://sourceforge.net/projects/mingw/).
2. Durante la instalación, selecciona `g++`, `gcc` y `mingw32-make`.

### Paso 2: Añadir MinGW al PATH

Asegúrate de que la ruta de instalación de MinGW esté en tu variable de entorno `PATH`. Deberías agregar algo como:

```sh
C:\MinGW\bin
```

### Paso 3: Abrir la Terminal de Comandos

Abre una terminal de comandos (CMD) o PowerShell en la carpeta principal del proyecto donde están las carpetas `Source Files` y `Header Files`.

### Paso 4: Comando de Compilación

Ejecuta el siguiente comando para compilar el proyecto:

```bash
g++ -o authenticator_program "Source Files/authenticator.cpp" "Source Files/filesystem.cpp" "Source Files/main.cpp" -I "Header Files" -Wl,-subsystem,console
```

### Paso 5: Ejecutar el Programa

Una vez compilado, ejecuta el programa usando el siguiente comando en la misma terminal:

```bash
authenticator_program
```

## Cómo Funciona

1. El programa carga los datos almacenados en `users/users_data.txt`.
2. Autentica usuarios verificando las contraseñas que ya están almacenadas en el sistema de archivos.
3. Al ejecutar el programa, puedes probar la autenticación de un usuario predefinido.

## Archivo de Usuarios

El archivo `users/users_data.txt` contiene información sobre los usuarios en el siguiente formato:

```txt
<nombre_archivo>,<contraseña_hasheada>,<email>,<nombre_completo>,<adminType>,<acceso_a_pisos>,<acceso_a_sensores>
```

Ejemplo:

```txt
tatis.txt,bf859476c9388014979c9e38dc87aa37ee12a197db7690d8a7b882e2fe03d2aa,tatis@peru.com,Tatis Para,1,1,1,1,1,1,1,1
```

## Notas Importantes

- El archivo `users_data.txt` se actualizará cada vez que se ejecute el programa para guardar nuevos datos.
- Si el archivo `users_data.txt` no existe, se creará automáticamente.
- Puedes agregar más usuarios manualmente en el archivo `users_data.txt` si lo deseas.



g++ "Source Files/authenticator.cpp" "Source Files/main.cpp" "Source Files/filesystem.cpp" -o authenticator -I"Header Files"

g++ "Source Files/main.cpp" "Source Files/filesystem.cpp" -o authenticator -I"Header Files"