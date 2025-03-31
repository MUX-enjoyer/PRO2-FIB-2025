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