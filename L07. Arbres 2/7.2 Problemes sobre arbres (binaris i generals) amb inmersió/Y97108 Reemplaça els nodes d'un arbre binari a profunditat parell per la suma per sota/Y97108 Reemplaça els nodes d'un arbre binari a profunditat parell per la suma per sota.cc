#include <iostream>
using namespace std;

#include "bintree.hh"
using namespace pro2;

BinTree<int> aux_sum_below_at_even_depth(BinTree<int> t, int depth, int& sum) {
    if (t.empty()) return BinTree<int>();

    int sum_left = 0, sum_right = 0;
    BinTree<int> left, right;
    left = aux_sum_below_at_even_depth(t.left(), depth+1, sum_left);
    right = aux_sum_below_at_even_depth(t.right(), depth+1, sum_right);
    
    sum = t.value() + sum_left + sum_right;

    if (depth % 2 == 0) return BinTree<int>(sum, left, right);
    else return BinTree<int>(t.value(), left, right);
}

/**
 * @brief Retorna l'arbre `t` reemplaçant els valors dels nodes a profunditat parell per la suma per sota
 *
 * @param t L'arbre binari original.
 *
 * @returns Un arbre binari R amb la mateixa estructura que t.
 * Per a cada posició p de t i R, si p és a profunditat senar,
 * llavors t i R tenen el mateix valor a posició p.
 * En canvi, si p es a profunditat parell, llavors el valor de R a posició
 * p és la suma de tots els valors que es troben a t a posició p i per sota.
 */
BinTree<int> sum_below_at_even_depth(BinTree<int> t) {
    int suma = 0;
    return aux_sum_below_at_even_depth(t, 0, suma);
}