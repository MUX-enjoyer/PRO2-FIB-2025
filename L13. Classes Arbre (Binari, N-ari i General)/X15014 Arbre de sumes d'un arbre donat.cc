/* Pre: cert */
/* Post: l'arbre asum és l'arbre suma del p.i. */
void arb_sumes(Arbre<int> &asum) const {
    asum.primer_node = aux_arb_sumes(primer_node);
}

node_arbre* aux_arb_sumes(node_arbre* node) const {
    if (node == NULL) return NULL;

    node_arbre* n = new node_arbre;
    n->info = node->info;

    if (node->segE != NULL) {
        n->segE = aux_arb_sumes(node->segE);
        n->info += n->segE->info;
    } 
    if (node->segD != NULL) {
        n->segD = aux_arb_sumes(node->segD);
        n->info += n->segD->info;
    }
    
    return n;
}