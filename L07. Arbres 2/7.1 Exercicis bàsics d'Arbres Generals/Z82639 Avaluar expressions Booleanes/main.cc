#include <iostream>
using namespace std;

#include "tree-io.hh"
#include "eval.hh"
using namespace pro2;

int main() {
    Tree<string> t;
    while (cin >> t) {
        cout << evaluate(t) << endl;
    }
}