#include "PageTable.hpp"

// Inicializa la tabla de páginas poniendo todas las entradas en -1
PageTable::PageTable() {
    pageTable.resize(256, -1);
}

// Verifica si el número de página es válido, o sea, si está dentro del rango.
bool PageTable::isValidPage(size_t pageNumber) const {
    return pageNumber < pageTable.size();
}

// Obtiene el número de marco asociado a una página dada.
int PageTable::getFrame(size_t pageNumber) const {
    if (!isValidPage(pageNumber)) {
        return -1; // Si la página no está cargada, devuelve -1.
    }
    return pageTable[pageNumber];
}

// Actualiza la entrada de una página en la tabla con el número de marco correspondiente.
void PageTable::updatePage(size_t pageNumber, int frameNumber) {
    if (isValidPage(pageNumber)) {
        pageTable[pageNumber] = frameNumber;
    }
}
