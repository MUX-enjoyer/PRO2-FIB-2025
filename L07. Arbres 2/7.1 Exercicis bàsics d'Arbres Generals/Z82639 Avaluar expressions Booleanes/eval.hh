#include <iostream>
#include <string>
#include "tree.hh"

/**
 * @brief Avalua un arbre no buit que representa una expressió Booleana.
 *
 * L'expressió és sobre l'1 (true) i el 0 (fals) i els operadors
 * 'and', 'or', i 'not'.
 *
 * @pre L'arbre és no buit i l'expressió és correcta, és a dir, els operands
 * 'and' i 'or' tenen més d'un operand, i l'operador 'not' en té només 1.
 *
 * @param t Arbre que representa l'expressió.
 * @return Resultat de l'avaluació de l'expressió.
 */
bool evaluate(pro2::Tree<std::string> t);