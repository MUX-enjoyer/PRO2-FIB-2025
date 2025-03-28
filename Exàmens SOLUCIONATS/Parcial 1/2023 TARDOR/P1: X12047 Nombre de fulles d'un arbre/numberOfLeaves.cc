#include "numberOfLeaves.hh"

int numberOfLeaves(BinTree<int> t) {
    if (t.empty()) return 0;
    else if (t.left().empty() && t.right().empty()) {
        return 1;
    }
    else {
        int esq, dreta;
        esq = dreta = 0;
        if (!t.left().empty()) esq = numberOfLeaves(t.left());
        if (!t.right().empty()) dreta = numberOfLeaves(t.right());
        return esq + dreta;
    }
}