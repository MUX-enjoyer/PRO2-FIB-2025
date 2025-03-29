#include <iostream>
using namespace std;

#include "tree-io.hh"
using namespace pro2;

#include "Z19994 Mostra carpetes indentades.cc"

int main() {
    Tree<string> t;
    int indent_size;
    while (cin >> indent_size >> t) {
        print_folders(t, indent_size);
    }
}