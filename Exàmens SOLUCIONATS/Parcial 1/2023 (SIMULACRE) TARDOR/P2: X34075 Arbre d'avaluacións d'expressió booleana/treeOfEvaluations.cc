#include "treeOfEvaluations.hh"

BinTree<bool> treeOfEvaluations(BinTree<string> t) {
    BinTree<bool> left, right;
    bool valor = false;
    if (t.left().empty() && t.right().empty()) {
        if (t.value() == "true") valor = true;
        else valor = false;
    }
    else {
        left = treeOfEvaluations(t.left());
        if (t.value() == "not") valor = !left.value();
        else {
            right = treeOfEvaluations(t.right());
            if (t.value() == "and") valor = left.value() && right.value();
            else valor = left.value() || right.value();
        }
    }
    return BinTree<bool>(valor, left, right);
}