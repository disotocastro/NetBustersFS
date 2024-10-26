#ifndef ADDRESSTRANSLATOR_HPP
#define ADDRESSTRANSLATOR_HPP

#include "PageTable.hpp"
#include "PhysicalMemory.hpp"

/**
 * @class AddressTranslator
 * @brief Traductor de direcciones virtuales a físicas, gestionando fallos de página y traducción de direcciones.
 */
class AddressTranslator {
public:
    /**
     * @brief Constructor que inicializa el traductor de direcciones con las clases necesarias.
     * @param pageTable Referencia a la tabla de páginas utilizada para la traducción.
     * @param physicalMemory Referencia a la memoria física donde se almacenan las páginas.
     */
    AddressTranslator(PageTable& pageTable, PhysicalMemory& physicalMemory);

    /**
     * @brief Traduce una dirección lógica a una dirección física.
     * @param logicalAddress La dirección lógica a traducir.
     * @return La dirección física correspondiente.
     */
    int translateAddress(int logicalAddress);

    /**
     * @brief Maneja un fallo de página, cargando la página desde el respaldo.
     * @param pageNumber El número de la página que causó el fallo.
     */
    void handlePageFault(int pageNumber);

    /**
     * @brief Obtiene el número de fallos de página ocurridos.
     * @return El número de fallos de página.
     */
    int getPageFaultCount() const;

private:
    /**
     * @brief Referencia a la tabla de páginas.
     */
    PageTable& pageTable;

    /**
     * @brief Referencia a la memoria física donde se almacenan las páginas cargadas.
     */
    PhysicalMemory& physicalMemory;

    /**
     * @brief Contador de fallos de página.
     */
    int pageFaultCount = 0;
};

#endif // ADDRESSTRANSLATOR_HPP
