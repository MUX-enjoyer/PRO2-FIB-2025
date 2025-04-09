/* Pre: cert */
/* Post: el resultat indica si x es troba al p.i. o no */
bool buscar(const T& x) const {
    return buscarRecursiu(primer_node, x);
}

bool buscarRecursiu(node_arbreGen* node, const T& valor) const {
    if (node == NULL) return false;
    if (node->info == valor) return true;

    for (int i = 0; i < node->seg.size(); ++i) {
        if (buscarRecursiu(node->seg[i], valor)) return true;
    }
    return false;
}