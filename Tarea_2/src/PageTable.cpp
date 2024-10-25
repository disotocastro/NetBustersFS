#include "PageTable.hpp"

// Constructor: Inicializa la tabla de páginas con todas las entradas en -1 para indicar que no están cargadas.
PageTable::PageTable() {
    pageTable.resize(256, -1);
}

// Verifica si el número de página es válido (dentro del rango).
bool PageTable::isValidPage(size_t pageNumber) const {
    return pageNumber < pageTable.size();
}

// Obtiene el número de marco asociado a una página.
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

// Verifica si una página está cargada en la memoria física.
bool PageTable::isPageLoaded(size_t pageNumber) const {
    return isValidPage(pageNumber) && pageTable[pageNumber] != -1;
}
