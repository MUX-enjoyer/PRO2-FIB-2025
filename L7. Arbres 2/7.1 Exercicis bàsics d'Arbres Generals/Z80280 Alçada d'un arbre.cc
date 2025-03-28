#include <iostream>
using namespace std;

#include "tree-io.hh"
#include "tree.hh"
using namespace pro2;

/**
 * @brief Calcula l'alçada d'un arbre
 * @param t Un arbre.
 * @returns L'alçada de l'arbre, segons la definició anterior.
 */
int tree_height(Tree<int> t) {
    if (t.empty()) return 0;

    int max_size = 0;
    for (int i = 0; i < t.num_children(); ++i) {
        int size = tree_height(t.child(i));
        if (size > max_size) max_size = size;
    }
    return 1+max_size;
}