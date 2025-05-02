#include <iostream>
using namespace std;

#include "tree-io.hh"
#include "tree.hh"

using namespace pro2;

/**
 * @brief Transforma una expressió en la seva representació com a `string`.
 *
 * Una expressió està formada per operadors (`+`, `*` i `-`), i
 * operands (naturals), que són nodes d'un arbre. Els operands tenen dos
 * fills o més, i els operands són fulles (no tenen fills).
 *
 * L'expressió representada com a `string` és de la següent manera. Per a
 * operands: cal retornar l'operand mateix. Per a operadors, cal retornar
 * els fills de l'operador, separats per l'operador, amb un espai entre 
 * operand i operadors, i tot el conjunt sempre entre parèntesis.
 *
 * @pre L'arbre representa una expressió ben formada
 *
 * @param t L'arbre que representa l'expressió.
 * @returns La representació com a `string` de `t`
 */
string expression_to_string(Tree<string> t) {
    if (t.empty()) return "";
    if (t.num_children() == 0) return t.value();

    string expression = "(";
    expression.append(expression_to_string(t.child(0)));

    for (int i = 1; i < t.num_children(); ++i) {
        expression.append(" ");
        expression.append(t.value());
        expression.append(" ");
        expression.append(expression_to_string(t.child(i)));
    }
    
    expression.append(")");
    return expression;
}