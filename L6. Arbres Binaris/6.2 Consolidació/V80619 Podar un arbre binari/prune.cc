using namespace std;
#include "prune.hh"
using namespace pro2;


/**
 * @brief Poda les branques amb valor `x` d'un arbre binari.
 *
 * Retorna un nou arbre binari que és una còpia de `t`
 * però sense les branques que contenen el valor `x`.
 * Alhora retorna si la poda ha tingut èxit o no s'ha podat res.
 * 
 * @param t Arbre binari.
 * @param x Valor de les branques a podar.
 *
 * @return Retorna una parella (`std::pair`) amb l'arbre podat 
 *         i un booleà que és `true` si s'ha podat alguna branca 
 *         i `false` si l'arbre resultat és igual que `t`.
 */
std::pair<pro2::BinTree<int>, bool> prune_tree(pro2::BinTree<int> t, int x) {
    if (t.empty()) return {BinTree<int>(), false};
    if (t.value() == x) return {BinTree<int>(), true};

    pair<BinTree<int>, bool> left, right;
    left = prune_tree(t.left(), x);
    right = prune_tree(t.right(), x);
    BinTree<int> arbre_podat(t.value(), left.first, right.first);
    bool haSigutPodat = left.second || right.second;
    return {arbre_podat, haSigutPodat};
}