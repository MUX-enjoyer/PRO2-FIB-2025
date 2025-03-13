#include <iostream>
#include <map>
#include <vector>

using namespace std;

/**
 * Pre: L'entrada consisteix en una seqüència de parelles (nom, t), on `nom` és un string sense espais i `t` és un enter dins del rang [-10^6, 10^6].
 * Post: Els usuaris i els seus valors s'han emmagatzemat a `usuaris` i `per_valor` segons el seu valor t.
 */
void llegir_usuaris(map<string, int>& usuaris, map<int, vector<string>>& per_valor) {
    string nom;
    int t;
    while (cin >> nom >> t) {
        usuaris[nom] = t;
        per_valor[t].push_back(nom);
    }
}

/**
 * Pre: `usuaris` conté una llista d'usuaris amb els seus valors t, i `per_valor` agrupa usuaris segons aquests valors.
 * Post: Es mostra una línia per usuari amb els seus compatibles, en ordre alfabètic.
 */
void trobar_compatibles(const map<string, int>& usuaris, const map<int, vector<string>>& per_valor) {
    map<string, int>::const_iterator it;
    for (it = usuaris.begin(); it != usuaris.end(); ++it) {
        const string& usuari = it->first;
        int valor = it->second;
        int oposat = -valor;

        cout << usuari;

        if (per_valor.count(oposat)) {
            vector<string>::const_iterator it2;
            for (it2 = per_valor.at(oposat).begin(); it2 != per_valor.at(oposat).end(); ++it2) {
                if (*it2 != usuari) cout << " " << *it2;
            }
        }
        cout << endl;
    }
}

/**
 * Pre: L'entrada segueix el format indicat.
 * Post: Es llegeixen els usuaris i es mostra la seva compatibilitat.
 */
int main() {
    map<string, int> usuaris;
    map<int, vector<string>> per_valor;

    llegir_usuaris(usuaris, per_valor);
    trobar_compatibles(usuaris, per_valor);

}
