using namespace std;
#include <iostream>

#include <stack>
#include <string>

// Pre:  s és un string no buit que conté només caràcters "(,),[,]"
// Post: Retorna el nombre de canvis que calen per a convertir l’string en ben parentitzat.

int canvis_necessaris_benparentitzat(const string s) {
    int canvis = 0;
    stack<char> pila;
    for (int i = 0; i < s.size(); ++i) {
        char c = s[i];
        if (c == '(' || c == '[') pila.push(c);
        else if (pila.empty()) ++canvis;
        else if (c == ')' && pila.top() == '(') pila.pop();
        else if (c == ']' && pila.top() == '[') pila.pop();
        else {
            pila.pop();
            ++canvis;
        }
    }
    return canvis;
}


int main() {
    string s;
    while(cin >> s) {
        cout << canvis_necessaris_benparentitzat(s) << endl;
    }
}