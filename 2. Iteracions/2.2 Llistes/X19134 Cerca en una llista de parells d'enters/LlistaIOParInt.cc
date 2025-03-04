using namespace std;
#include <iostream>

#include <list>

#include "ParInt.hh"

void LlegirLlistaParInt(list<ParInt>& l) {
    ParInt parell;
    while (parell.llegir()) l.push_front(parell);
}