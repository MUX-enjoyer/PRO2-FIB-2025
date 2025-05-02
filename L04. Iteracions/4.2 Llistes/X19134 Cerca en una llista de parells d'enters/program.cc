using namespace std;
#include <iostream>

#include <list>

#include "ParInt.hh"
#include "LlistaIOParInt.hh"

ParInt BuscarLlista(list<ParInt> llista, int n) {
    int repe = 0;
    int suma = 0;
    while (!llista.empty()) {
        if (llista.front().primer() == n) {
            ++repe;
            suma += llista.front().segon();
        }
        llista.pop_front();
    }
    return ParInt(repe, suma);
}


int main() {
    list<ParInt> llista;
    LlegirLlistaParInt(llista);
    int n;
    cin >> n;
    ParInt resultats = BuscarLlista(llista, n);
    cout << n << ' ' << resultats.primer() << ' ' << resultats.segon() << endl;
}