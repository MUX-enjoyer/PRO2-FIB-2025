#include <iostream>
#include <map>
#include <sstream>

using namespace std;

/**
 * Pre: L'entrada conté una seqüència de parells (paraula_A, paraula_B) seguit d'una línia buida,
 *      després una seqüència de paraules en l'idioma A a traduir.
 * Post: Es mostra la traducció de cada paraula en l'idioma B o "<not found>" si no es troba en el diccionari.
 */
int main() {
    map<string, string> diccionari;
    string linia, paraula_A, paraula_B;

    // Llegir la primera part (diccionari)
    while (getline(cin, linia) && !linia.empty()) {
        istringstream ss(linia);
        ss >> paraula_A >> paraula_B;
        diccionari[paraula_A] = paraula_B;
    }

    // Llegir la segona part (paraules a traduir)
    while (cin >> paraula_A) {
        if (diccionari.count(paraula_A)) cout << diccionari[paraula_A] << endl;
        else cout << "<not found>" << endl;
    }

}
