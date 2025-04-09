/* Pre: cert */
/* Post: asum és un arbre amb la mateixa estructura que el p.i.
         i cada node és la suma del node corresponent al p.i
         i tots els seus descendents al p.i. */
void arbsuma(ArbreNari& asum) const {
    asum.primer_node = aux_arb_sumes(primer_node);
}

node_arbreNari* aux_arb_sumes(node_arbreNari* node) const {
    if (node == NULL) return NULL;

    node_arbreNari* n = new node_arbreNari;
    n->info = node->info;
    
    n->seg = vector<node_arbreNari*>(node->seg.size());

    for (int i = 0; i < node->seg.size(); ++i) {
        if (node->seg[i] != NULL) {
            n->seg[i] = aux_arb_sumes(node->seg[i]);
            n->info += n->seg[i]->info;
        }
    }
    return n;
}