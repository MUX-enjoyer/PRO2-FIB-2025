using namespace std;
using namespace pro2;

#include "BinTree.hh"


bool comparar_fulles(BinTree<int> t, int& val_fulla, bool& primera_fulla) {
    if (t.empty()) return true;

    if (t.right().empty() && t.left().empty()) {
        if (primera_fulla) {
            val_fulla = t.value();
            primera_fulla = false;
            return true;
        }
        else {
            if (t.value() == val_fulla) return true;
            else return false;
        }
    }
    else {
        if (comparar_fulles(t.left(), val_fulla, primera_fulla)) {
            return comparar_fulles(t.right(), val_fulla, primera_fulla);
        }
        else return false;
    }
}

int main() {
    BinTree<int> t;
    comparar_fulles(t, -1, true);
}



bool comparar_fulles(BinTree<int> t, int& val_node, bool& primer_node) {
    if (t.empty()) return true;
    if (t.right().empty() && t.left().empty()) return true;

    if (primer_node) {
        val_node = t.value();
        primer_node = false;
    }
    bool left, right;
    left = comparar_fulles(t.left(), val_node, primer_node);
    if (!left) return false;
    right = comparar_fulles(t.right(), val_node, primer_node);
    if (!right) return false;
    return (t.value() == primer_node);
}