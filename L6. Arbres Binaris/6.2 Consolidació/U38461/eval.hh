#include <iostream>
#include <string>
#include "util.hh"
#include "bintree.hh"


/**
 * @brief Avalua un arbre no buit que representa una expressió binària.
 *
 * L'expressió binària és sobre els naturals i els operadors +, -, i *. 
 * Les operacions de l'arbre no produeixen errors d'_overflow_ (sobreeiximent).
 *
 * @pre L'arbre és no buit i l'expressió binària és correcta.
 *
 * @param t Arbre que representa l'expressió binària.
 * @return Resultat de l'avaluació de l'expressió.
 */
int evaluate(pro2::BinTree<std::string> t);