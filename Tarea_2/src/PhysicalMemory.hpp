#ifndef PHYSICALMEMORY_HPP
#define PHYSICALMEMORY_HPP

#include <vector>
#include <stddef.h>

/**
 * @class PhysicalMemory
 * @brief Gestiona los marcos de la memoria física y actúa como respaldo para páginas no cargadas.
 */
class PhysicalMemory {
public:

    PhysicalMemory(size_t numberOfFrames);

    /**
     * @brief Obtiene un marco libre en la memoria física.
     * @return El número del primer marco libre encontrado, o -1 si no hay marcos disponibles.
     */
    int getFreeFrame() const;

    /**
     * @brief Almacena una página en un marco específico de la memoria física.
     * @param frameNumber El número del marco donde se almacenará la página.
     * @param pageData Los datos de la página que se van a almacenar.
     */
    void storePage(int frameNumber, const std::vector<char>& pageData);

    /**
     * @brief Carga una página desde el respaldo.
     * @param pageNumber El número de la página que se va a cargar.
     * @return Los datos de la página solicitada.
     */
    std::vector<char> loadPage(size_t pageNumber) const;

private:
    /**
     * @brief Vector que almacena los datos de cada marco.
     */
    std::vector<std::vector<char>> frames;

    /**
     * @brief Vector de booleanos que indica si un marco está disponible.
     */
    std::vector<bool> frameAvailability;

    /**
     * @brief Arreglo en memoria que actúa como el respaldo.
     */
    std::vector<std::vector<char>> storage;
};

#endif // PHYSICALMEMORY_HPP
