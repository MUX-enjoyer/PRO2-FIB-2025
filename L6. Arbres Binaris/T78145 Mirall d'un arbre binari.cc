#include <iostream>
using namespace std;

#include "bintree-io.hh"
#include "bintree.hh"
using namespace pro2;

/**
* @brief Retorna un arbre binari que és el mirall de l'arbre `t`.
* 
* Un arbre binari és el mirall d'un altre si les seves branques esquerra i dreta
* estan intercanviades recursivament en tots els nodes.
* 
* @param t L'arbre binari original.
* 
* @returns Un arbre binari que és el mirall de l'arbre `t`.
*/
BinTree<int> reverse_tree(BinTree<int> t) {
    if (t.empty()) return BinTree<int>();

    BinTree<int> left, right;
    left = reverse_tree(t.right());
    right = reverse_tree(t.left());
    return BinTree<int>(t.value(), left, right);
}