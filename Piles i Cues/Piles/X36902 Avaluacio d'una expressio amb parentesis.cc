#include <iostream>
using namespace std;
#include <stack>

int main() {
    char x;
    int pos = 0, i = 1;
    stack<char> pila;
    cin >> x;
    while(x != '.') {
        if ((x == '(' || x == '[')) pila.push(x);
        else if (!pila.empty()) {
            if (pila.top() == '(' && x == ')') pila.pop();
            else if (pila.top() == '[' && x == ']') pila.pop();
            else if (pos == 0) pos = i;
        }
        else if (pos == 0) pos = i;
        ++i;
        cin >> x;
    }
    if (pos != 0) cout << "Incorrecte " << pos << endl;
    else if (!pila.empty()) cout << "Incorrecte " << i-1 << endl;
    else cout << "Correcte" << endl;
}