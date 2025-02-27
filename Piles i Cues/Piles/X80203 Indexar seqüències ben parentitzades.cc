#include <iostream>
using namespace std;

#include <string>
#include <stack>

int main() {
    string x;
    stack<int> pila;
    while(cin >> x) {
        int mida = x.size();
        int cont = 1;
        for (int i = 0; i < mida; ++i) {
            if (x[i] == '(') {
                pila.push(cont);
                cout << x[i] << pila.top();
                ++cont;
            }
            else if (x[i] == ')') {
                cout << x[i] << pila.top();
                pila.pop();
            }
        }
        cout << endl;
    }
}