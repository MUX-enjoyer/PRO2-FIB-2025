#include "evaluate.hh"

bool evaluate(const BinTree<string> t) {
    if (t.left().empty() && t.right().empty()) {
        if (t.value() == "true") return true;
        else return false;
    }
    else {
        bool left = evaluate(t.left());
        if (t.value() == "not") return !left;
        else if (t.value() == "and") {
            if (!left) return false;
            else return evaluate(t.right());
        }
        else if (t.value() == "or") {
            if (left) return true;
            else return evaluate(t.right());
        }
    }
    return true;
}