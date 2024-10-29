#include "PageTable.hpp"
#include "PhysicalMemory.hpp"
#include "AddressTranslator.hpp"

#include <iostream>
#include <fstream>
#include <iomanip>

int main() {
    // Iniciar componentes
    PageTable pageTable;
    PhysicalMemory physicalMemory(256); // Memoria física con 256 marcos

    // Crear el traductor de direcciones
    AddressTranslator translator(pageTable, physicalMemory);

    // Abrir el archivo de entradas
    std::ifstream inputFile("addresses.txt");
    if (!inputFile) {
        std::cerr << "Error: No se pudo abrir el archivo addresses.txt" << std::endl;
        return 1;
    }

    // Encabezado de la tabla
    std::cout << std::left
              << std::setw(5) << "#" 
              << "| " << std::setw(18) << "Dirección Lógica "
              << " | " << std::setw(18) << "Dirección Física "
              << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    // Leer cada dirección lógica y traducirla
    int logicalAddress;
    int count = 1;
    while (inputFile >> logicalAddress) {
        try {
            int physicalAddress = translator.translateAddress(logicalAddress);
            
            // Imprimir la información de dirección lógica y física
            std::cout << std::left
                      << std::setw(5) << count
                      << "| " << std::setw(18) << logicalAddress
                      << "| " << std::setw(18) << physicalAddress
                      << std::endl;

            count++;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    // Cerrar el archivo de direcciones
    inputFile.close();

    // Mostrar estadísticas de fallos de página
    std::cout << "\nTotal de fallos de página: " << translator.getPageFaultCount() << std::endl;

    return 0;
}
