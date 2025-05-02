#include <iostream>
using namespace std;

#include "tree-io.hh"
using namespace pro2;


void aux_print_folders(Tree<string> t, int indent_size, int depth) {
    if (t.empty()) return;

    for (int i = 0; i < depth*indent_size; ++i) cout << " ";
    cout << t.value() << endl;
    for (int i = 0; i < t.num_children(); ++i) {
        aux_print_folders(t.child(i), indent_size, depth+1);
    }
}

/**
 * @brief Mostra un arbre de carpetes i fitxers a la sortida en format 
 * indentat
 *
 * Per exemple:
 * ```
 * projecte
 *     documents
 *     codi font
 *         main.cc
 *         Makefile
 *     jocs de prova
 *         publics
 *             sample-1.inp
 *             sample-2.inp
 *         privats
 *     Reunio 2024-12-10
 *
 * ```
 *
 * Cal notar que la última línia és buida per poder veure la separació 
 * amb altres arbres de carpetes
 *
 * Malgrat això no és rellevant per al problema, les fulles de l'arbre 
 * són fitxers o carpetes i la resta són sempre carpetes.
 *
 * @param t Un arbre de strings a on cada `string` representa una carpeta 
 * o un fitxer.
 * @param indent_size Número d'espais d'indentació per a cada nivell.
 *
 * @pre `indent_size` > 0.
 *
 * @post S'ha mostrat per la sortida estàndard l'arbre `t` amb un nivell
 * d'indentació d'`indent_size` espais per a cada nivell de profunditat.
 */
void print_folders(Tree<string> t, int indent_size) {
    aux_print_folders(t, indent_size, 0);
    cout << endl;
}