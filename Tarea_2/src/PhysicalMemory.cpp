#include "PhysicalMemory.hpp"
#include <stdexcept> // Para manejar excepciones

// Constructor: Inicializa la memoria física con el número de marcos especificado.
PhysicalMemory::PhysicalMemory(size_t numberOfFrames) {
    // Redimensionar los vectores para los marcos y su disponibilidad.
    frames.resize(numberOfFrames, std::vector<char>(256, 0));
    frameAvailability.resize(numberOfFrames, true);
}

// Busca un marco libre en la memoria.
// Devuelve -1 si no hay marcos disponibles.
int PhysicalMemory::getFreeFrame() const {
    for (size_t i = 0; i < frameAvailability.size(); ++i) {
        if (frameAvailability[i]) {
            return static_cast<int>(i); // Devolver el primer marco libre disponible.
        }
    }
    return -1; // No se encontraron marcos disponibles.
}

// Almacena una página en un marco específico de la memoria.
void PhysicalMemory::storePage(int frameNumber, const std::vector<char>& pageData) {
    if (frameNumber < 0 || frameNumber >= static_cast<int>(frames.size())) {
        throw std::out_of_range("El número de marco está fuera del rango permitido.");
    }
    if (pageData.size() != 256) {
        throw std::invalid_argument("El tamaño de la página no es correcto. Se esperaba 256 bytes.");
    }
    frames[frameNumber] = pageData;
    frameAvailability[frameNumber] = false; // Marcar el marco como ocupado.
}

// Lee un byte específico desde un marco y un desplazamiento dados.
char PhysicalMemory::readByte(int frameNumber, int offset) const {
    if (frameNumber < 0 || frameNumber >= static_cast<int>(frames.size()) ||
        offset < 0 || offset >= 256) {
        throw std::out_of_range("La dirección solicitada está fuera de rango.");
    }
    return frames[frameNumber][offset];
}
