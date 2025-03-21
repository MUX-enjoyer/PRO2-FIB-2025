#include "eval.hh"
#include "util.hh"
using namespace std;
using namespace pro2;


/**
 * @brief Avalua un arbre no buit que representa una expressió binària.
 *
 * L'expressió binària és sobre els naturals i els operadors +, -, i *. 
 * Les operacions de l'arbre no produeixen errors de sobreeiximent 
 * (_overflow_).
 *
 * @pre L'arbre és no buit i l'expressió binària és correcta.
 *
 * @param t Arbre que representa l'expressió binària.
 * @return Resultat de l'avaluació de l'expressió.
 */
int evaluate(BinTree<string> t) {
    if (t.empty()) return 0;

    string s = t.value();
    if (is_number(s)) return string_to_int(s);

    int l = evaluate(t.left());
    int r = evaluate(t.right());
    
    if (s == "+") return l + r;
    else if (s == "-") return l - r;
    else return l*r;
}