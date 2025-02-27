#include <iostream>
using namespace std;

#include <string>
#include <set>

int main() {
    set<string> activitat, totes_activitats, cap_activitat;
    set<string>::iterator it_act, it_tot, it_cap;

    string cognom;
    cin >> cognom;
    while (cognom != ".") {
        cap_activitat.insert(cognom);
        cin >> cognom;
    }
    
    int n;
    cin >> n;
    totes_activitats = cap_activitat;
    for (int i = 0; i < n; ++i) {
        cin >> cognom;
        while (cognom != ".") {
            activitat.insert(cognom);
            cin >> cognom;
        }
        for (it_act = activitat.begin(); it_act != activitat.end(); ++it_act) {
            it_cap = cap_activitat.find(*it_act);
            if (it_cap != cap_activitat.end()) cap_activitat.erase(it_cap);
        }
        for (it_tot = totes_activitats.begin(); it_tot != totes_activitats.end();) {
            it_act = activitat.find(*it_tot);
            if (it_act == activitat.end()) it_tot = totes_activitats.erase(it_tot);
            else ++it_tot;
        }
        activitat.clear();
    }

    cout << "Totes les activitats:";
    for (it_tot = totes_activitats.begin(); it_tot != totes_activitats.end(); ++it_tot) {
        cout << ' ' << *it_tot;
    }
    cout << endl << "Cap activitat:";
    for (it_cap = cap_activitat.begin(); it_cap != cap_activitat.end(); ++it_cap) {
        cout << ' ' << *it_cap;
    }
    cout << endl;
}