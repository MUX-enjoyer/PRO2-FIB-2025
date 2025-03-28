#include <iostream>
#include <string>
#include <map>

using namespace std;

void afegir(map<string, int>& persones, map<int, int>& repeticions) {
    string name;
    int numcoins;
    cin >> name >> numcoins;
    ++repeticions[numcoins];
    persones[name] = numcoins;
}

void borrar(map<string, int>& persones, map<int, int>& repeticions) {
    string name;
    cin >> name;
    --repeticions[persones[name]];
    persones.erase(name);
}

int contar(map<int, int> repeticions) {
    int numcoins;
    cin >> numcoins;

    // MOLT INEFICIENT
    // map<string, int>::const_iterator it;
    // for (it = persones.begin(); it != persones.end(); ++it) {
    //     if (it->second == numcoins) ++cont;
    // }

    return repeticions[numcoins];
}

int main() {
    map<string, int> persones;
    map<int, int> repeticions;
    string s;
    while (cin >> s) {
        if (s == "ADD") afegir(persones, repeticions);
        else if (s == "DELETE") borrar(persones, repeticions);
        else if (s == "NUMPEOPLE") cout << contar(repeticions) << endl;
    }
}
