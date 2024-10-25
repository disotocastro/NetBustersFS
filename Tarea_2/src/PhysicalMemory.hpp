#ifndef PHYSICALMEMORY_HPP
#define PHYSICALMEMORY_HPP

#include <vector>
#include <stddef.h>

/**
 * @class PhysicalMemory
 * @brief Gestiona los marcos de la memoria física.
 */
class PhysicalMemory {
public:
    /**
     * @brief Constructor que inicializa la memoria física con el número de marcos especificado.
     * @param numberOfFrames El número de marcos de memoria física a inicializar.
     */
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
     * @brief Lee un byte específico desde un marco y desplazamiento de la memoria física.
     * @param frameNumber El número del marco del cual se va a leer el byte.
     * @param offset El desplazamiento dentro del marco.
     * @return El byte leído de la memoria física.
     */
    char readByte(int frameNumber, int offset) const;

private:
    /**
     * @brief Vector que almacena los datos de cada marco.
     */
    std::vector<std::vector<char>> frames;

    /**
     * @brief Vector de booleanos que indica si un marco está disponible.
     */
    std::vector<bool> frameAvailability;
};

#endif // PHYSICALMEMORY_HPP
