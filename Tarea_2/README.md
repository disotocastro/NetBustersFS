# Diseño de un Administrador de Memoria Virtual

## Descripción

Esta tarea consiste en la implementación de un sistema para gestionar la memoria virtual en un entorno de sistemas operativos. El objetivo es simular un traductor de direcciones virtuales a físicas, manejando la tabla de páginas, fallos de página, y almacenamiento en memoria física. La memoria virtual se organiza en páginas y marcos, y el sistema incluye la carga de páginas desde un respaldo cuando ocurre un fallo de página.

Se desarrolla siguiendo los conceptos explicados en el libro "Operating System Concepts" de Silberschatz, Galvin, y Gagne, que describe cómo funciona la memoria virtual, la gestión de la tabla de páginas y el reemplazo de páginas.

## Compilación y Ejecución

Para compilar y ejecutar el programa, sigue los siguientes comandos:

```sh
g++ -Wall -Wextra -std=c++17 src/*.cpp -o program
./program
```

## Referencias y Atribuciones

Este proyecto se basa en los conceptos descritos en *Operating System Concepts* (Silberschatz, Galvin, Gagne), así como en recursos en línea como los artículos de GeeksforGeeks:

1. El libro **Operating System Concepts** como la referencia principal para la implementación, asegurando la cobertura teórica y los algoritmos utilizados.
2. Los artículos de **GeeksforGeeks** como apoyo adicional para comprender los conceptos generales sobre **memoria virtual** y **gestión de memoria**.

## Integrantes

- Juan Diego Soto Castro - C07722
- William Morales Fuentes - C15222
- Andres Murillo Murillo - C15424
- Gypsi Tatiana Páramo López - C25795
- Alessandro Merino López - C14751

## Presentacion de resultados

Finalmente los resultados se presentan de esta forma en la terminal:

```txt
#    | Dirección Lógica  | Dirección Física 
------------------------------------------------------------
1    | 1                 | 1                 
2    | 256               | 256               
3    | 32768             | 512               
4    | 32769             | 513               
5    | 128               | 128               
6    | 65534             | 1022              
7    | 33153             | 1153              
8    | 12345             | 1337              
9    | 54321             | 1585              
10   | 9999              | 1807              
11   | 4096              | 2048              
12   | 2048              | 2304              
13   | 40960             | 2560              
14   | 512               | 2816              
15   | 45000             | 3272              
16   | 7890              | 3538              
17   | 6000              | 3696              
18   | 20480             | 3840              
19   | 1024              | 4096              
20   | 50000             | 4432              

Total de fallos de página: 18
```
