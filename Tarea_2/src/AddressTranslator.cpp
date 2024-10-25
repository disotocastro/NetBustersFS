#include "AddressTranslator.hpp"
#include <stdexcept>

// Constructor: Inicializa las referencias necesarias para traducir direcciones.
AddressTranslator::AddressTranslator(PageTable& pt, BackingStore& bs, PhysicalMemory& pm)
    : pageTable(pt), backingStore(bs), physicalMemory(pm), pageFaultCount(0) {}

// Traduce una dirección lógica a una dirección física.
int AddressTranslator::translateAddress(int logicalAddress) {
    // Obtener el número de página y el offset manualmente para darle un toque más personalizado.
    int pageNumber = logicalAddress / 256;
    int offset = logicalAddress - (pageNumber * 256); // Evitando el uso del operador %.

    // Comprobar si la página está cargada.
    int frameNumber = pageTable.getFrame(pageNumber);

    // Si la página no está cargada, manejar el fallo de página.
    if (frameNumber == -1) {
        handlePageFault(pageNumber);
        frameNumber = pageTable.getFrame(pageNumber); // Volver a verificar tras cargar la página.
    }

    // Calcular la dirección física de forma manual para hacerlo más natural.
    int physicalAddress = (frameNumber * 256) + offset;
    return physicalAddress;
}

// Maneja un fallo de página, cargando la página desde el respaldo.
void AddressTranslator::handlePageFault(int pageNumber) {
    // Aumentar el contador de fallos de página.
    pageFaultCount++;

    // Cargar la página desde el respaldo.
    std::vector<char> pageData = backingStore.loadPage(pageNumber);

    // Buscar un marco libre en la memoria física.
    int freeFrame = physicalMemory.getFreeFrame();
    if (freeFrame == -1) {
        throw std::runtime_error("No hay marcos disponibles para manejar el fallo de página.");
    }

    // Guardar la página en la memoria física y actualizar la tabla de páginas.
    physicalMemory.storePage(freeFrame, pageData);
    pageTable.updatePage(pageNumber, freeFrame);
}

// Retorna el número de fallos de página que han ocurrido.
int AddressTranslator::getPageFaultCount() const {
    return pageFaultCount;
}
