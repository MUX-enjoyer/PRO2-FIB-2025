#include "numNegative.hh"
#include "utils.hh"

// Pre:  t és un arbre no buit que representa una expressió correcta
//       sobre els naturals i els operadors +,-,*.
//       Les operacions no produeixen errors d'overflow.
//       int cont = 0;
// Post: Si t.value() és un numero retorna num en int
//       Si t.value() és un operand retorna el resultat de la operació
//       amb les seves dues branques 
int contar_avaluacions_negatives(BinTree<string> t, int& cont) {
    if (isNumber(t.value())) return mystoi(t.value());
    else {
        int valor, esq, dreta;
        esq = contar_avaluacions_negatives(t.left(), cont);
        dreta = contar_avaluacions_negatives(t.right(), cont);
        if (t.value() == "+") valor = esq + dreta;
        else if (t.value() == "-") valor = esq - dreta;
        else valor = esq * dreta; // if (t.value() == "*")

        if (valor < 0) ++cont;
        return valor;
    }
}

int numNegative(BinTree<string> t) {
    int resultat = 0;
    contar_avaluacions_negatives(t, resultat);
    return resultat;
}