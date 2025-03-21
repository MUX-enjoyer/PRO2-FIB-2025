#include <iostream>
using namespace std;

#include "bintree-io.hh"
#include "bintree.hh"
using namespace pro2;

/**
 * @brief Retorna l'arbre de sumes de `t`.
 *
 * L'arbre de sumes és un arbre binari amb la mateixa forma 
 * de `t` però a on cada valor conté la suma dels valors 
 * del subarbre que penja de la mateixa posició a `t`.
 *
 * @param t L'arbre binari original.
 *
 * @returns L'arbre de sumes de `t`.
 */
BinTree<int> tree_of_sums(BinTree<int> t) {
    if (t.empty()) return BinTree<int>();


    BinTree<int> left, right;
    int suma = t.value();
    if (!t.left().empty()) {
        left = tree_of_sums(t.left());
        suma += left.value();
    }

    if (!t.right().empty()) {
        right = tree_of_sums(t.right());
        suma += right.value();
    }
    return BinTree<int>(suma, left, right);
}