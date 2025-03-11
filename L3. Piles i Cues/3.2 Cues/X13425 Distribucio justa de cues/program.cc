#include <iostream>
using namespace std;

#include <queue>
#include <string>

#include "CuaIOParInt.hh"
#include "ParInt.hh"

int main() {
    queue<ParInt> cua_0, cua_1, cua_2;
    llegirCuaParInt(cua_0);
    int espera_1 = 0;
    int espera_2 = 0;

    while (!cua_0.empty()) {
        if (espera_1 <= espera_2) {
            cua_1.push(cua_0.front());
            espera_1 += cua_0.front().segon();
            cua_0.pop();
        } else {
            cua_2.push(cua_0.front());
            espera_2 += cua_0.front().segon();
            cua_0.pop();
        }
    }
    escriureCuaParInt(cua_1);
    cout << endl;
    escriureCuaParInt(cua_2);
}