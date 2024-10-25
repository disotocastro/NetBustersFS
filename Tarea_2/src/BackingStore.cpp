#include "BackingStore.hpp"
#include <stdexcept> // Para manejar excepciones

// Constructor: Inicializa el respaldo con el número de páginas especificado.
BackingStore::BackingStore(size_t size) {
    // Redimensionar el almacenamiento según el número de páginas.
    storage.resize(size);
    for (size_t i = 0; i < size; ++i) {
        // Inicializar cada página con un valor relacionado al número de página (para probar el comportamiento).
        std::vector<char> page(PAGE_SIZE);
        for (size_t j = 0; j < PAGE_SIZE; ++j) {
            page[j] = static_cast<char>((i + j) % 256); // Valor basado en la suma del índice de la página y el byte.
        }
        storage[i] = page;
    }
}

// Cargar una página desde el respaldo.
std::vector<char> BackingStore::loadPage(size_t pageNumber) const {
    // Verificar que el número de página esté en el rango correcto.
    if (pageNumber >= storage.size()) {
        throw std::out_of_range("El número de página está fuera de rango.");
    }
    // Devolver la página solicitada.
    return storage[pageNumber];
}
