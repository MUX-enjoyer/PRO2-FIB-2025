#include <iostream>
using namespace std;

#include "bintree-io.hh"
#include "bintree.hh"
using namespace pro2;

/**
 * @brief Cerca un valor en un arbre binari.
 * 
 * @param t Arbre binari.
 * @param x Valor a cercar.
 *
 * @returns `true` si `x` es troba en algun node de l'arbre `t`,
 *          `false` en cas contrari.
 */
bool cerca_valor(BinTree<int> t, int x) {
    if (t.empty()) return false;
    else if (t.value() == x) return true;
    
    return cerca_valor(t.left(), x) || cerca_valor(t.right(), x);
}