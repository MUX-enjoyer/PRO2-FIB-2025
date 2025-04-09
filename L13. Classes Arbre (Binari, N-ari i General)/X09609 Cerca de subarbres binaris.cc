 /* Pre: p.i. = A, asub es buit */
 /* Post: si A conte x, asub es el subarbre d'A resultat de la cerca;
    si A no conte x, asub es buit */
void sub_arrel(Arbre& asub, const T& x) {
    int dist_min = -1;
    trobar_sub_arrel(primer_node, asub, x, 0, dist_min);
}

void trobar_sub_arrel(node_arbre* node, Arbre& asub, const T& x, int nivell, int& dist_min) {
    if (node != NULL) {
        ++nivell;
        if (node->info == x && (dist_min == -1 || nivell < dist_min)) {
            asub.primer_node = copia_node_arbre(node);
            dist_min = nivell;
        }
        else {
            trobar_sub_arrel(node->segE, asub, x, nivell, dist_min);
            trobar_sub_arrel(node->segD, asub, x, nivell, dist_min);
        }
    }
}