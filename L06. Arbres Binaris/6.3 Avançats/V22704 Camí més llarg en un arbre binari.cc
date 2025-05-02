#include <iostream>
using namespace std;

#include "bintree-inline.hh"
#include "bintree-io.hh"
#include "bintree.hh"
#include "vector-io.hh"
using namespace pro2;

/**
 * @brief Retorna els valors dels nodes del camí més llarg de l'arbre binari `t`.
 *
 * Un camí va des de l'arrel de l'arbre fins a una full (un node sense fills).
 * Si hi ha més d'un camí màxim, cal retornar el que va per les branques de més
 * a l'esquerra possible.
 *
 * @param t L'arbre binari.
 *
 * @returns Els valors dels nodes del camí més llarg de `t`.
 */
vector<int> longest_leftmost_path(BinTree<int> t) {
    if (t.empty()) return vector<int>();
 
    vector<int> left, right;
    left = longest_leftmost_path(t.left());
    right = longest_leftmost_path(t.right());

    if (left.size() < right.size()) {
        right.insert(right.begin(), t.value());
        return right;
    } else {
        left.insert(left.begin(), t.value());
        return left;
    }
}