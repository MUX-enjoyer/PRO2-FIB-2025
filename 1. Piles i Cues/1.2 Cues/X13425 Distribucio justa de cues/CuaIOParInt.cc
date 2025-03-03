#include <iostream>
using namespace std;

#include <queue>

#include "ParInt.hh"

void llegirCuaParInt(queue<ParInt>& c) {
    int x, y;
    cin >> x >> y;
    while(x != 0 && y != 0) {
        c.push({x,y});
        cin >> x >> y;
    }
}

void escriureCuaParInt(queue<ParInt> c) {
    while (!c.empty()) {
        cout << c.front().primer() << ' ' << c.front().segon() << endl;
        c.pop();
    }
}