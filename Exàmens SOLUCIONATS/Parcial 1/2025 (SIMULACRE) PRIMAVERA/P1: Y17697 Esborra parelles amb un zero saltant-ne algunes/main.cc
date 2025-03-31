#include <iostream>
#include <list>
#include <sstream>
using namespace std;

/**
 * @brief Esborra parelles d'una llista que tinguin un 0 al camp 
 *        `second`, saltant-ne `skip`
 *
 * `skip` és el nombre de parelles que, tenint un zero en el camp 
 * `second`, NO s'han d'esborrar de la llista, comptant des del 
 * principi. `skip` pot ser més gran que les parelles que tenen 0 
 * al camp `second`.
 *
 * @param  L     La llista de parelles
 * @param  skip  El nombre de parelles a saltar
 *
 * @pre   `skip` >= 0
 */
void remove_zeros_skipping(list<pair<string, int>>& L, int skip) {
    list<pair<string, int>>::iterator it = L.begin();
    while (it != L.end()) {
        if (it->second == 0) {
            if (skip < 1) it = L.erase(it);
            else {
                --skip;
                ++it;
            }
        }
        else ++it;
    }
}

int read_int(string line) {
    istringstream iss(line);
    int n;
    iss >> n;
    return n;
}

template <typename A, typename B>
list<pair<A, B>> read_list_of_pairs(string input) {
    A a;
    B b;
    list<pair<A, B>> result;

    istringstream iss(input);
    while (iss >> a >> b) {
        result.push_back({a, b});
    }
    return result;
}

void show_list_of_pairs(list<pair<string, int>>& L) {
    auto it = L.begin();
    if (it != L.end()) {
        cout << it->first << ' ' << it->second;
        while (++it != L.end()) {
            cout << ' ' << it->first << ' ' << it->second;
        }
    }
    cout << endl;
}

int main() {
    string str_list, str_skip;
    while (getline(cin, str_list) && getline(cin, str_skip)) {
        auto L = read_list_of_pairs<string, int>(str_list);
        remove_zeros_skipping(L, read_int(str_skip));
        show_list_of_pairs(L);
    }
}