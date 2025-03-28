#include "tree-io.hh"
#include "tree.hh"
using namespace pro2;

#include <iostream>
using namespace std;

/**
 * @brief Retorna un arbre que és el mirall de l'arbre `t`.
 * 
 * Un arbre és el mirall d'un altre si les seves branques esquerra i dreta
 * estan intercanviades recursivament en tots els nodes.
 * 
 * @param t L'arbre original.
 * 
 * @returns Un arbre que és el mirall de l'arbre `t`.
 */
Tree<int> tree_mirror(Tree<int> t) {
    if (t.empty()) return Tree<int>();

    vector<Tree<int>> fills;
    for (int i = t.num_children()-1; i >= 0; --i) {
        Tree<int> fill = tree_mirror(t.child(i));
        fills.push_back(fill);
    }
    return Tree<int>(t.value(), fills);
}