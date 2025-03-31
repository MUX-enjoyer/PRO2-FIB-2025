using namespace std;
#include <iostream>
#include <string>
#include <map>
#include <set>

int main() {
    string nom, ciutat;
    int any;
    map<pair<int, string>, set<string>> coincidencies;
    while (cin >> nom >> any >> ciutat) {
        coincidencies[{any, ciutat}].insert(nom);
    }

    map<pair<int, string>, set<string>>::iterator it;
    for (it = coincidencies.begin(); it != coincidencies.end(); ++it) {
        if (it->second.size() > 1) {
            cout << it->first.first << " " << it->first.second << ":";
            set<string>::iterator it2;
            for (it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
                cout << " " << *it2;
            }
            cout << endl;
        }
    }
}