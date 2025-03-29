#include <iostream>
#include <fstream>
#include <map>
using namespace std;

#include "bintree-io.hh"
#include "bintree.hh"
using namespace pro2;

#include "Z78925 Avaluar expressions binàries amb variables.cc"

map<string, int> read_env(istream& in) {
    map<string, int> env;
    string name;
    int value;
    while (in >> name && name != ".") {
        in >> value;
        env[name] = value;
    }
    return env;
}

int main() {
    BinTree<string> t;
    while (cin >> t) {
        assert(!t.empty());
        auto env = read_env(cin);
        cout << tree_eval_env(t, env) << endl;
    }
}