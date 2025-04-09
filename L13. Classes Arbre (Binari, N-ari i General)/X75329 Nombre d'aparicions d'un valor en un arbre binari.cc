/* Pre: cert */
/* Post: el resultat indica el nombre d'aparicions de x en el p.i. */
int freq(const T& x) const {
    return freq_aux(primer_node, x);
}


int freq_aux(const node_arbre* node, const T& x) const {
    if (node == NULL) return 0;
    
    int comptador = 0;
    if (node->info == x) ++comptador;

    comptador += freq_aux(node->segE, x);
    comptador += freq_aux(node->segD, x);

    return comptador;
}