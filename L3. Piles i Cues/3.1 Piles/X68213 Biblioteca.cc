#include <iostream>
using namespace std;

#include <string>
#include <vector>
#include <stack>

int main() {
    int n, opcio;
    char x;
    cin >> n >> x >> opcio;
    vector<stack<string>> piles(n);
    
    while (opcio != 4) {
        int num_pila;
        if (opcio == 1) {
            string llibre;
            cin >> llibre >> num_pila;
            piles[num_pila-1].push(llibre);
        }
        if (opcio == 2) {
            int n_llibres;
            cin >> n_llibres >> num_pila;
            for (int i = 0; i < n_llibres; ++i) {
                piles[num_pila-1].pop();
            }
        }
        if (opcio == 3) {
            cin >> num_pila;
            stack<string> copia_pila = piles[num_pila-1];
            cout << "Pila de la categoria " << num_pila << endl;
            for (int i = 0; !copia_pila.empty(); ++i) {
                cout << copia_pila.top() << endl;
                copia_pila.pop();
            }
            cout << endl;
        }

        cin >> x >> opcio;
    }
}