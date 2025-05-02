#include "bintree-inline.hh"
#include "bintree-io.hh"
#include "bintree.hh"
#include "vector-io.hh"
using namespace pro2;

#include <chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;

#include "T47104 Arbre binari de graus de desequilibri.cc"

void main_inline() {
    string line;
    while (getline(cin, line)) {
        auto t = bintree_inline_read<int>(line);
        auto D = bintree_of_height_diffs(t);
        bintree_inline_write(D);
    }
}

void main_visual() {
    BinTree<int> t;
    while (cin >> t) {
        auto D = bintree_of_height_diffs(t);
        cout << D;
    }
}

int main() {
    string format, line;
    getline(cin, format);  // determina el format dels arbres
    if (format == "inline") {
        main_inline();
    } else {
        main_visual();
    }
}
