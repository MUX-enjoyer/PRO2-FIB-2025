using namespace std;
#include <iostream>

#include <list>

void inter(list<int>& uno, const list<int>& dos ) {
 /* Pre: uno = U */
 /* Post: uno pasa a ser la interseccion de U y dos */
    list<int>::iterator it1 = uno.begin();
    list<int>::const_iterator it2 = dos.begin();
    while (it1 != uno.end() && it2 != dos.end()) {
        if (*it1 < *it2) it1 = uno.erase(it1);
        else if (*it1 > *it2) ++it2;
        else {
            ++it1;
            ++it2;
        }
    }
    // Elimina els elements sobrants a la fi de uno (si n'hi ha)
    uno.erase(it1, uno.end());
}