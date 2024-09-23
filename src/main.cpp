#include <iostream>
#include "SistemaArchivosFAT.hpp"

int main() {
    SistemaArchivosFAT fs;

    // 1
    std::cout << "Estado inicial de la Unidad, Directorio, FAT y Tabla:\n";
    fs.imprimir();

    // 2
    std::cout << "\nCreando archivo 'archivoA.txt' con datos 'A'\n";
    fs.crear("archivoA.txt");
    fs.escribir("archivoA.txt", "A");

    // 3
    std::cout << "\nEstado de la Unidad, Directorio, FAT y Tabla después de crear 'archivoA.txt':\n";
    fs.imprimir();

    // 4

  
    std::cout << "\nAgregando usuario 'morasebas47' con contraseña 'mnopq11'\n";
    fs.crear("user7.txt");
    fs.escribir("user7.txt", "morasebas47, mnopq11");

    std::cout << "\nAgregando usuario 'josandrade1' con contraseña 'rstuv22'\n";
    fs.crear("user8.txt");
    fs.escribir("user8.txt", "josandrade1, rstuv22");

    // 5
    std::cout << "\nEstado de la Unidad, Directorio, FAT y Tabla después de agregar usuarios:\n";
    fs.imprimir();

    return 0;
}
