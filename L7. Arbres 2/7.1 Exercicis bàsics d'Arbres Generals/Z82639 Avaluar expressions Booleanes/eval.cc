#include "eval.hh"

bool evaluate(pro2::Tree<std::string> t) {
    if (t.empty()) return false;
    if (t.num_children() == 0) return t.value() == "1";
    if (t.value() == "not") return !evaluate(t.child(0));

    bool result = evaluate(t.child(0));
    for (int i = 1; i < t.num_children(); ++i) {
        if (t.value() == "and") {
            result = result and evaluate(t.child(i));
        }
        else if (t.value() == "or") {
            result = result or evaluate(t.child(i));
        }
    }
    return result;
}