#include <iostream>
#include "bintree-io.hh"
#include "prune.hh"
using namespace pro2;
using namespace std;

int main() {
    int          x;
    BinTree<int> t;
    while (cin >> t >> x) {
        auto res = prune_tree(t, x);
        if (res.second) {
            cout << res.first << endl;
        } else {
            cout << "No s'ha trobat " << x << endl << endl;
        }
    }
}