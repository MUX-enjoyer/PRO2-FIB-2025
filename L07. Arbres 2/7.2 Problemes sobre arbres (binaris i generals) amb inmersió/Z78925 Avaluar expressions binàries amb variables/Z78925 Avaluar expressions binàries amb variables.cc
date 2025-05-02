#include <iostream>
#include <fstream>
#include <map>
using namespace std;

#include "bintree-io.hh"
#include "bintree.hh"
using namespace pro2;

#include "util.hh"

/**
 * @brief Avalua una expressió binària amb variables
 *
 * L'expressió és sobre els naturals i els operadors `+`, `-`, i `*`.
 * A més, hi ha un diccionari `env` que emmagatzema els valors d'un
 * conjunt de variables que poden aparèixer a l'arbre.
 *
 * @pre `t` és no buit. Totes les variables que apareixen a `t`
 *       estan definides a `env`. Les opercions expressades per
 *       l'arbre no produeixen errors d'_overflow_
 * 
 * @param t Arbre amb l'expressió binària.
 * @param env Diccionari amb parelles (nom de variable, valor). Aquest 
 *            diccionari no es pot modificar.
 */
int tree_eval_env(BinTree<string> t, const map<string, int>& env) {
    if (t.empty()) return 0;
    if (is_number(t.value())) return string_to_int(t.value());
    if (is_var_name(t.value())) return env.at(t.value());
    
    int left, right;
    left = tree_eval_env(t.left(), env);
    right = tree_eval_env(t.right(), env);
    if (t.value() == "-") return left-right;
    else if (t.value() == "+") return left+right;
    else return left*right;
}