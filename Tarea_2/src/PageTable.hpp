#ifndef PAGETABLE_HPP
#define PAGETABLE_HPP

#include <vector>
#include <stddef.h>

/**
 * @class PageTable
 * @brief Encargada de manejar la tabla de páginas.
 */
class PageTable {
public:
    /**
     * @brief Constructor por defecto.
     */
    PageTable();

    /**
     * @brief Obtiene el número de marco asociado a una página.
     * @param pageNumber El número de la página a consultar.
     * @return El número de marco asociado, o -1 si la página no está cargada.
     */
    int getFrame(size_t pageNumber) const;

    /**
     * @brief Actualiza la entrada de una página en la tabla.
     * @param pageNumber El número de la página a actualizar.
     * @param frameNumber El número del marco donde se almacena la página.
     */
    void updatePage(size_t pageNumber, int frameNumber);

    /**
     * @brief Verifica si una página está cargada en la memoria física.
     * @param pageNumber El número de la página a verificar.
     * @return true si la página está cargada, false en caso contrario.
     */
    bool isPageLoaded(size_t pageNumber) const;

private:
    /**
     * @brief Verifica si el número de página es válido.
     * @param pageNumber El número de la página a verificar.
     * @return true si el número de página es válido, false en caso contrario.
     */
    bool isValidPage(size_t pageNumber) const;

    /**
     * @brief Vector que almacena los números de marco por cada página.
     * Si la página no está cargada, el valor será -1.
     */
    std::vector<int> pageTable;
};

#endif // PAGETABLE_HPP
