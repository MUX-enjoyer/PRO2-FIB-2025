#ifndef CLASS_ParInt_HH
#define  CLASS_ParInt_HH

#include <iostream>
using namespace std;
#include "ParInt.hh"

void llegirCuaParInt(queue<ParInt>& c);
// Pre: c és buida; el canal estandar d’entrada conté un nombre
// parell d’enters, acabat pel parell 0 0
// Post: s’han encuat a c els elements llegits fins al 0 0 (no inclòs)

void escriureCuaParInt(queue<ParInt> c);
// Pre: cert
// Post: s’han escrit al canal estandar de sortida els elements de c

#endif