#include <iostream>
using namespace std;

#include "bintree-io.hh"
#include "bintree.hh"
using namespace pro2;

/**
 * @brief Calcula l'alçada d'un arbre binari
 * @param t Un arbre binari.
 * @returns L'alçada de l'arbre, segons la definició anterior.
 */
int height(BinTree<int> t) {
    if (t.empty()) return 0;
    return 1 + max(height(t.left()), height(t.right()));
}