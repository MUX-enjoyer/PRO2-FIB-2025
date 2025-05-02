#include <chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;

#include "bintree-inline.hh"
#include "bintree-io.hh"
#include "bintree.hh"
using namespace pro2;


pair<BinTree<int>, int> sort_tree_aux(const BinTree<int>& t) {
    if (t.empty()) return {BinTree<int>(), 0};

    pair<BinTree<int>, int> left, right;
    left = sort_tree_aux(t.left());
    right = sort_tree_aux(t.right());
    int total_sum = left.second + right.second + t.value();

    if (right.second < left.second) {
        return {BinTree<int>(t.value(), right.first, left.first), total_sum};
    }
    else {
        return {BinTree<int>(t.value(), left.first, right.first), total_sum};
    }
}

/**
 * @brief Retorna l'arbre `t` ordenat per sumes.
 *
 * @param t L'arbre binari original.
 *
 * @returns L'arbre resultat d'ordenar `t` per sumes.
 */
BinTree<int> sort_tree(BinTree<int> t) {
    return sort_tree_aux(t).first;
}
