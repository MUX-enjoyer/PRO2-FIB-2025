#include <iostream>
#include <string>
#include <cstdlib>

#include <vector>

using namespace std;

#include "BinTree.hh"

int getIdVar(string s)
{
 return atoi(s.substr(1).c_str());
}

int main()
{
 string s1, s2, s3, s4, s5, s6, s7;
 int numvars;
 cin >> s1 >> numvars >> s2;

 // Disposem de 3 vectors de tamany numvars on a cada element del vector hi ha un arbre d'enters
 // Els arbres de vars, contenen els arbres tn
 vector<BinTree<int>> vars(numvars);
 // Els arbres mida_vars, contenen un arbre de la mateixa estructura que tn
 // però a cada node en comptes del valor de l'arbre hi ha la mida dels nodes de la branca corresponent
 vector<BinTree<int>> mida_vars(numvars, BinTree<int>(0));
 // De la mateixa manera els arbres suma_vars contenen la suma de la seva branca
 vector<BinTree<int>> suma_vars(numvars, BinTree<int>(0));

 while (cin >> s1 >> s2) {
  if (s1[0] == 't') {
   int idvar = getIdVar(s1);
   if (s2 == "=BinTree(") {
    int value;
    cin >> value >> s3 >> s4 >> s5 >> s6 >> s7;
    int idvar1 = getIdVar(s4);
    int idvar2 = getIdVar(s6);
    vars[idvar] = BinTree<int>(value, vars[idvar1], vars[idvar2]);
    mida_vars[idvar] = BinTree<int>(1 + mida_vars[idvar1].value() + mida_vars[idvar2].value(), mida_vars[idvar1], mida_vars[idvar2]);
    suma_vars[idvar] = BinTree<int>(value + suma_vars[idvar1].value() + suma_vars[idvar2].value(), suma_vars[idvar1], suma_vars[idvar2]);
   } else if (s2 == "=") {
    cin >> s3 >> s4;
    int idvar1 = getIdVar(s3);
    if (s4 == ".left();") {
      if (vars[idvar1].empty() || vars[idvar1].left().empty()) {
        vars[idvar] = BinTree<int>();
        mida_vars[idvar] = suma_vars[idvar] = BinTree<int>(0);
      }
      else {
        vars[idvar] = vars[idvar1].left();
        mida_vars[idvar] = mida_vars[idvar1].left();
        suma_vars[idvar] = suma_vars[idvar1].left();
      }
    } else {
      if (vars[idvar1].empty() || vars[idvar1].right().empty()) {
        vars[idvar] = BinTree<int>();
        mida_vars[idvar] = suma_vars[idvar] = BinTree<int>(0);
      }
      else {
        vars[idvar] = vars[idvar1].right();
        mida_vars[idvar] = mida_vars[idvar1].right();
        suma_vars[idvar] = suma_vars[idvar1].right();
      }
    }
   }
  } else if (s1 == "cout<<") {
   int idvar = getIdVar(s2);
   cin >> s3;
   vars[idvar].setOutputFormat(BinTree<int>::INLINEFORMAT);
   cout << vars[idvar] << endl;
  } else if (s1 == "cout<<size(") {
   int idvar = getIdVar(s2);
   cin >> s3;
   cout << mida_vars[idvar].value() << endl;
  } else if (s1 == "cout<<sum(") {
   int idvar = getIdVar(s2);
   cin >> s3;
   cout << suma_vars[idvar].value() << endl;
  }
 }
}