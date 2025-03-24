#ifndef VSTACK_HH
#define VSTACK_HH

#include <cassert>
#include <string>
#include <vector>

/**
 * @class VStack
 *
 * @brief Una pila amb els tres mètodes `push`, `pop` i `top`, però a on `top` també permet
 * consultar elements per sota el cim.
 */
class VStack {
    std::vector<std::string> stack_;

 public:
    /**
     * @brief Afegeix un element a la pila, que esdevindrà el nou cim.
     *
     * @param s L'element a afegir.
     */
    void push(std::string s);

    /**
     * @brief Elimina l'element al cim de la pila.
     *
     * @pre La pila no està buida.
     */
    void pop();

    /**
     * @brief Retorna la mida de la pila.
     *
     * @returns La mida de la pila (un enter sense signe).
     */
    size_t size() const;

    /**
     * @brief Determina si la pila està buida.
     *
     * @returns `true` si la pila està builda, `false` altrament.
     */
    bool empty() const;

    /**
     * @brief Retorna un element a certa distància del cim de la pila.
     *
     * El cim és `top(0)`, l'element just sota és `top(-1)`, etc.
     *
     * - PRE: -size()+1 <= depth <= 0
     *
     * @param depth La distància des del cim, un enter <= 0.
     *
     * @returns L'element consultat.
     */
    std::string top(int depth) const;

    /**
     * @brief Determina si la pila conté un element.
     *
     * @param s L'element a cercar.
     *
     * @returns `true` si l'element és a la pila, `false` altrament.
     */
    bool contains(std::string s) const;
};

#endif