#include "PhysicalMemory.hpp"
#include <stdexcept> // Para manejar excepciones

// Se inicializa la memoria física con el número de marcos especificado.
PhysicalMemory::PhysicalMemory(size_t numberOfFrames) {
    // Se ajusta el tamaño de los vectores para los marcos y la disponibilidad.
    frames.resize(numberOfFrames, std::vector<char>(256, 0));
    frameAvailability.resize(numberOfFrames, true);
    
    // Se inicializa el respaldo con datos simulados para las páginas.
    storage.resize(256);
    for (size_t i = 0; i < 256; ++i) {
        std::vector<char> page(256);
        for (size_t j = 0; j < 256; ++j) {
            // Se llena cada página con valores basados en el índice y el byte.
            page[j] = static_cast<char>((i + j) % 256);
        }
        storage[i] = page;
    }
}

// Buscar un marco libre en la memoria física.
int PhysicalMemory::getFreeFrame() const {
    for (size_t i = 0; i < frameAvailability.size(); ++i) {
        if (frameAvailability[i]) {
            return static_cast<int>(i); // Se retorna el primer marco libre que encontramos.
        }
    }
    return -1; // Si no hay marcos disponibles, devolver -1.
}

// Guarda una página en un marco específico de la memoria física.
void PhysicalMemory::storePage(int frameNumber, const std::vector<char>& pageData) {
    if (frameNumber < 0 || frameNumber >= static_cast<int>(frames.size())) {
        throw std::out_of_range("El número de marco está fuera del rango permitido.");
    }
    if (pageData.size() != 256) {
        throw std::invalid_argument("El tamaño de la página no es correcto. Debe ser de 256 bytes.");
    }
    frames[frameNumber] = pageData;
    frameAvailability[frameNumber] = false; // Se marca el marco como ocupado.
}

// Cargar una página desde el respaldo.
std::vector<char> PhysicalMemory::loadPage(size_t pageNumber) const {
    // Verificar si el número de página está en el rango correcto.
    if (pageNumber >= storage.size()) {
        throw std::out_of_range("El número de página está fuera del rango.");
    }
    return storage[pageNumber]; // Devuelve la página solicitada.
}
