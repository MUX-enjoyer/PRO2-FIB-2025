#include "bintree-inline.hh"
#include "bintree-io.hh"
#include "bintree.hh"
using namespace pro2;

#include <set>
#include <iostream>
using namespace std;

set<int> union_set(set<int> set1, set<int> set2) {
    set<int> result;
    set<int>::iterator it;
    if (set1.size() < set2.size()) {
        for (it = set1.begin(); it != set1.end(); ++it) set2.insert(*it);
        return set2;
    }
    else {
        for (it = set2.begin(); it != set2.end(); ++it) set1.insert(*it);
        return set1;
    }
}

set<int> aux_values_at_depth(BinTree<int> t, int depth, int actual_depth) {
    if (t.empty()) return {};
    if (actual_depth == depth) return {t.value()};

    set<int> left, right;
    left = aux_values_at_depth(t.left(), depth, actual_depth+1);
    right = aux_values_at_depth(t.right(), depth, actual_depth+1);
    
    return union_set(left, right);
}

/**
 * @brief Retorna el conjunt dels valors dels nodes d'un arbre 
 *        binari que estan a certa profunditat
 * 
 * La profunditat d'un node és:
 * a) 1       si és l'arrel (no té pare).
 * b) p + 1   si el pare del node té profunditat `p`.
 * 
 * @param t     Arbre binari d'enters.
 * @param depth La profunditat dels nodes que es vol.
 *
 * @returns El conjunt de valors trobats a profunditat `depth`
 */
set<int> values_at_depth(BinTree<int> t, int depth) {
    return aux_values_at_depth(t, depth, 1);
}

int read_int(string line) {
    istringstream iss(line);
    int x;
    iss >> x;
    return x; 
}

ostream& operator<<(ostream& o, const set<int>& S) {
    o << "{";
    for (int x : S) {
        o << ' ' << x;
    }
    o << " }";
    return o;
}

void main_visual() {
    BinTree<int> t;
    int depth;
    while (cin >> t >> depth) {
        cout << values_at_depth(t, depth) << endl;
    }
}

void main_inline() {
    string line;
    while (getline(cin, line)) {
        BinTree<int> t = bintree_inline_read<int>(line);
        getline(cin, line);
        int depth = read_int(line);
        cout << values_at_depth(t, depth) << endl;
    }
}

int main() {
    string line;
    getline(cin, line);
    if (line == "visual") {
        main_visual();
    } else if (line == "inline") {
        main_inline();
    } else {
        assert(false);
    }
}
