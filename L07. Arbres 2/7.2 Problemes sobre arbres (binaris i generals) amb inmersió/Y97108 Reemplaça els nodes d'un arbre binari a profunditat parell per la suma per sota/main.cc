#include <chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;

#include "bintree-inline.hh"
#include "bintree-io.hh"
#include "bintree.hh"
using namespace pro2;

#include "Y97108 Reemplaça els nodes d'un arbre binari a profunditat parell per la suma per sota.cc"

void main_visual() {
    BinTree<int> t;
    while (cin >> t) {
        cout << sum_below_at_even_depth(t);
    }
}

void main_inline() {
    string line;
    while (getline(cin, line)) {
        BinTree<int> t = bintree_inline_read<int>(line);
        BinTree<int> D = sum_below_at_even_depth(t);
        bintree_inline_write(D);
    }
}

int main() {
    std::ios::sync_with_stdio(false);

    string format, line;
    getline(cin, format);  // determina el format dels arbres
    if (format == "inline") {
        main_inline();
    } else {
        main_visual();
    }
}
