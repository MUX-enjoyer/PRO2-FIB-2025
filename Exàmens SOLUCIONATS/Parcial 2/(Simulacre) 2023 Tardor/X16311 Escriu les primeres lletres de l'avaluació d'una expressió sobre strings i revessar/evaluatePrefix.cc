using namespace std;

#include "evaluatePrefix.hh"

// Helper function to fully evaluate an expression tree
string evaluateExp(const BinTree<string>& t) {
    if (t.empty()) return "";
    
    if (t.value() == "Concat") {
        return evaluateExp(t.left()) + evaluateExp(t.right());
    }
    else if (t.value() == "Reverse") {
        string left = evaluateExp(t.left());
        string reversed = "";
        for (int i = left.size() - 1; i >= 0; --i) {
            reversed += left[i];
        }
        return reversed;
    }
    else {
        return t.value(); // It's a leaf node with a string value
    }
}

// Optimized function to evaluate only the prefix needed
string evaluatePrefix(BinTree<string> t, int n) {
    if (n == 0) return "";
    if (t.empty()) return "";
    
    if (t.value() == "Concat") {
        string leftResult = evaluatePrefix(t.left(), n);
        if (leftResult.size() >= n) {
            return leftResult.substr(0, n);
        }
        // Need more characters from the right subtree
        int remaining = n - leftResult.size();
        string rightResult = evaluatePrefix(t.right(), remaining);
        return leftResult + rightResult;
    }
    else if (t.value() == "Reverse") {
        string left = evaluateExp(t.left());
        string reversed = "";
        for (int i = left.size() - 1; i >= 0; --i) {
            reversed += left[i];
        }
        return reversed.substr(0, n);
    }
    else {
        // It's a leaf node with a string value
        return t.value().substr(0, n);
    }
}