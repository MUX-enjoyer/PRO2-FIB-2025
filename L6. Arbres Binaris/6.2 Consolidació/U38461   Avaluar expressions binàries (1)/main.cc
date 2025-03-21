#include <iostream>
#include "bintree-io.hh"
#include "eval.hh"
using namespace pro2;
using namespace std;

int main() {
    BinTree<string> t;
    while (cin >> t and not t.empty()) {
        cout << evaluate(t) << endl;
    }
}