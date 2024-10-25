#include "PageTable.hpp"
#include "BackingStore.hpp"
#include "PhysicalMemory.hpp"
#include "AddressTranslator.hpp"

#include <iostream>
#include <fstream>
#include <iomanip>

int main() {
    // Inicializar componentes
    PageTable pageTable;
    BackingStore backingStore(256); // Respaldo con 256 páginas
    PhysicalMemory physicalMemory(256); // Memoria física con 256 marcos

    // Crear el traductor de direcciones
    AddressTranslator translator(pageTable, backingStore, physicalMemory);

    // Abrir el archivo de direcciones lógicas
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
              << " | " << std::setw(10) << "Valor "
              << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    // Leer cada dirección lógica y traducirla
    int logicalAddress;
    int count = 1;
    while (inputFile >> logicalAddress) {
        try {
            int physicalAddress = translator.translateAddress(logicalAddress);
            char value = physicalMemory.readByte(physicalAddress / 256, physicalAddress % 256);

            // Imprimir los resultados usando numeración y separadores verticales
            std::cout << std::left
                      << std::setw(5) << count
                      << "| " << std::setw(18) << logicalAddress
                      << "| " << std::setw(18) << physicalAddress
                      << "| " << std::setw(10) << static_cast<int>(value)
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
