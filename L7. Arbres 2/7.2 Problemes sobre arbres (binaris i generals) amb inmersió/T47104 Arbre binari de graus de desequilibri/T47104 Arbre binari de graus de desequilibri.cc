#include "bintree-inline.hh"
#include "bintree-io.hh"
#include "bintree.hh"
#include "vector-io.hh"
using namespace pro2;

#include <chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;

BinTree<int> aux_bintree_of_height_diffs(BinTree<int> t, int& height) {
    if (t.empty()) return BinTree<int>();

    int left_height = 0, right_height = 0;
    BinTree<int> left = aux_bintree_of_height_diffs(t.left(), left_height);
    BinTree<int> right = aux_bintree_of_height_diffs(t.right(), right_height);

    height = 1 + max(left_height, right_height);
    int balance_factor = left_height - right_height;
    
    return BinTree<int>(balance_factor, left, right);
}

/**
 * @brief Retorna l'arbre de graus de desequilibri de `t`.
 *
 * @param t L'arbre binari original.
 * @returns L'arbre de graus de desequilibri de `t`.
 */
BinTree<int> bintree_of_height_diffs(BinTree<int> t) {
    int height;
    return aux_bintree_of_height_diffs(t, height);
}