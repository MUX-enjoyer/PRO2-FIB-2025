#include <iostream>
using namespace std;

#include <string>
#include <set>
#include <map>

int main() {
    set<string> cap_act;
    map<string, int> assistencia_act;

    string cognom;
    cin >> cognom;
    while (cognom != ".") {
        cap_act.insert(cognom);
        cin >> cognom;
    }
    
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> cognom;
        while (cognom != ".") {
            cap_act.erase(cognom);
            ++assistencia_act[cognom];
            cin >> cognom;
        }
    }

    cout << "Totes les activitats:";
    map<string, int>::iterator it_tot;
    for (it_tot = assistencia_act.begin(); it_tot != assistencia_act.end(); ++it_tot) {
        if (it_tot->second == n) cout << ' ' << it_tot->first;
    }
    
    cout << endl << "Cap activitat:";
    set<string>::iterator it_cap;
    for (it_cap = cap_act.begin(); it_cap != cap_act.end(); ++it_cap) {
        cout << ' ' << *it_cap;
    }
    cout << endl;
}