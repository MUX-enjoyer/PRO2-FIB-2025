#include <iostream>
using namespace std;

#include <queue>

#include "ParInt.hh"

void llegirCuaParInt(queue<ParInt>& c) {
    ParInt parell_enters;
    while(parell_enters.llegir()) {
        c.push(parell_enters);
    }
}

void escriureCuaParInt(queue<ParInt> c) {
    while(!c.empty()) {
        ParInt parell_enters = c.front();
        parell_enters.escriure();
        c.pop();
    }
}