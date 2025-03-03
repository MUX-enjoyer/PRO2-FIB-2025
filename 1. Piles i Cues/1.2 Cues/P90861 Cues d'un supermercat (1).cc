#include <iostream>
using namespace std;

#include <queue>
#include <sstream>
#include <string>
#include <vector>

int main() {
    int n;
    cin >> n;
    string x;
    cin.ignore();  // Ignora el salt de linea buit després de llegir 'n'

    vector<queue<string>> cues(n);

    for (int i = 0; i < n; ++i) {
        string line;
        getline(cin, line);     // Agafem tota la linea sencera i la posem a line
        stringstream ss(line);  // Dividim line en paraules dins ss
        while (ss >> x) {
            cues[i].push(x);
        }
    }

    cout << "SORTIDES" << endl
         << "--------" << endl;
    while (cin >> x) {
        if (x == "SURT") {
            int cua;
            cin >> cua;
            if (cua <= n && cua >= 1 && !cues[cua - 1].empty()) {
                cout << cues[cua - 1].front() << endl;
                cues[cua - 1].pop();
            }
        } else if (x == "ENTRA") {
            string nom;
            int cua;
            cin >> nom >> cua;
            if (cua <= n && cua >= 1) cues[cua - 1].push(nom);
        }
    }

    cout << endl
         << "CONTINGUTS FINALS" << endl
         << "-----------------" << endl;
    for (int i = 1; i <= n; ++i) {
        cout << "cua " << i << ':';
        while (!cues[i - 1].empty()) {
            cout << ' ' << cues[i - 1].front();
            cues[i - 1].pop();
        }
        cout << endl;
    }
}