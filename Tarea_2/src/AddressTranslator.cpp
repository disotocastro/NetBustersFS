#include "AddressTranslator.hpp"

// Se inicializa las referencias necesarias para traducir direcciones.
AddressTranslator::AddressTranslator(PageTable& pt, PhysicalMemory& pm)
    : pageTable(pt), physicalMemory(pm), pageFaultCount(0) {}

// Traduce una dirección lógica a una dirección física.
int AddressTranslator::translateAddress(int logicalAddress) {
    // Obtener el número de página y el offset
    int pageNumber = logicalAddress / 256;
    int offset = logicalAddress - (pageNumber * 256);

    // Comprobar si la página está cargada.
    int frameNumber = pageTable.getFrame(pageNumber);

    // Si la página no está cargada, manejar el fallo de página.
    if (frameNumber == -1) {
        handlePageFault(pageNumber);
        frameNumber = pageTable.getFrame(pageNumber);
    }

    return (frameNumber * 256) + offset;
}

// Maneja un fallo de página
void AddressTranslator::handlePageFault(int pageNumber) {
    // Aumentar el contador de fallos de página.
    pageFaultCount++;

    // Se cargar la página desde el respaldo en PhysicalMemory.
    std::vector<char> pageData = physicalMemory.loadPage(pageNumber);

    // Buscar un marco libre en la memoria física
    int freeFrame = physicalMemory.getFreeFrame();

    // Guardar la página en la memoria física y actualizar la tabla de páginas.
    physicalMemory.storePage(freeFrame, pageData);
    pageTable.updatePage(pageNumber, freeFrame);
}

// Retorna el número de fallos de página que han ocurrido.
int AddressTranslator::getPageFaultCount() const {
    return pageFaultCount;
}
