#include <iostream>
using namespace std;

#include "bintree-io.hh"
#include "bintree.hh"
using namespace pro2;

/**
 * @brief Retorna l'arbre de mides de `t`.
 *
 * L'arbre de mides és un arbre binari amb la mateixa forma 
 * que `t` però a on cada valor conté la quantitat total de 
 * nodes del subarbre que penja de la mateixa posició a `t`.
 *
 * @param t L'arbre binari original.
 *
 * @returns L'arbre de mides de `t`.
 */
BinTree<int> tree_of_sizes(BinTree<int> t) {
    if (t.empty()) return BinTree<int>();


    BinTree<int> left, right;
    int mida = 1;
    if (!t.left().empty()) {
        left = tree_of_sizes(t.left());
        mida += left.value();
    }

    if (!t.right().empty()) {
        right = tree_of_sizes(t.right());
        mida += right.value();
    }
    return BinTree<int>(mida, left, right);

}