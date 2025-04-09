/* Pre: el parametre implicit no es buit */
/* Post: el resultat es la suma del cami de suma maxima del parametre implicit */
T max_suma_cami() const {
    return suma_max(primer_node);
}

int suma_max(const node_arbre* node) const {
    if (node == NULL) return 0;

    int suma = node->info;
    int suma_esq = suma_max(node->segE);
    int suma_dreta = suma_max(node->segD);

    if (suma_esq > suma_dreta) return suma + suma_esq;
    else return suma + suma_dreta;
}