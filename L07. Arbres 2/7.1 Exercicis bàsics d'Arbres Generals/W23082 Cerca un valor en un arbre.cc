#include <iostream>
using namespace std;

#include "tree-io.hh"
#include "tree.hh"
using namespace pro2;

/**
 * @brief Cerca un valor en un arbre.
 *
 * @param t Arbre.
 * @param x Valor a cercar.
 *
 * @returns Retorna `true` si `x` es troba en algun node de l'arbre `t`,
 *          `false` en cas contrari.
 */
bool tree_search(Tree<int> t, int x) {
    if (t.empty()) return false;
    if (t.value() == x) return true;

    for (int i = 0; i < t.num_children(); ++i) {
        if (tree_search(t.child(i), x)) return true;
    }
    return false;
}