#ifndef PRUNE_HH
#define PRUNE_HH

#include <utility>
#include "bintree.hh"

/**
 * @brief Poda les branques amb valor `x` d'un arbre binari.
 *
 * Cerca en un arbre binari totes les branques amb valor `x` i les elimina, retornant un nou arbre.
 * 
 * @param t Arbre binari.
 * @param x Valor de les branques a podar.
 *
 * @return Retorna una parella (`std::pair`) amb l'arbre podat i un booleà que és `true` si s'ha
 *         podat alguna branca i `false` si l'arbre resultat és igual que `t`.
 */
std::pair<pro2::BinTree<int>, bool> prune_tree(pro2::BinTree<int> t, int x);

#endif