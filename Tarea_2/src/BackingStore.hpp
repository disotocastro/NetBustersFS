#ifndef BACKINGSTORE_HPP
#define BACKINGSTORE_HPP

#include <vector>
#include <stddef.h>

/**
 * @class BackingStore
 * @brief Simula el respaldo de páginas no cargadas en memoria física.
 */
class BackingStore {
public:
    /**
     * @brief Constructor que inicializa el respaldo con un tamaño específico.
     * @param size El número de páginas en el respaldo.
     */
    BackingStore(size_t size);

    /**
     * @brief Carga una página desde el respaldo.
     * @param pageNumber El número de la página a cargar.
     * @return Un vector de caracteres que contiene los datos de la página.
     */
    std::vector<char> loadPage(size_t pageNumber) const;

private:
    /**
     * @brief Arreglo en memoria que actúa como el respaldo.
     */
    std::vector<std::vector<char>> storage;

    /**
     * @brief Tamaño de cada página (256 bytes).
     */
    static const size_t PAGE_SIZE = 256;
};

#endif // BACKINGSTORE_HPP
