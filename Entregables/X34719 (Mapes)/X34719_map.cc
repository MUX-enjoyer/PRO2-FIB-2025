using namespace std;
#include <iostream>
#include <set>
#include <string>
#include <map>

struct info {
    set<string> webs;
    int ultim_acces = 0;
    int n_accessos = 0;
    bool esBot = false;
};


int main() {
    map<string, info> log;

    string IP, web;
    int temps;

    while (cin >> IP >> web >> temps) {
        log[IP].webs.insert(web);
        if (temps - log[IP].ultim_acces < 100) {
            ++log[IP].n_accessos;
            if (log[IP].n_accessos == 20) log[IP].esBot = true;
        }
        else log[IP].n_accessos = 1;

        log[IP].ultim_acces = temps;
    }

    map<string, info>::iterator it;
    for (it = log.begin(); it != log.end(); ++it) {
        if (it->second.esBot) {
            cout << it->first;
            set<string>::iterator it2;
            for (it2 = it->second.webs.begin(); it2 != it->second.webs.begin(); ++it2) {
                cout << " " << *it2;
            }
            cout << endl;
        }
    }
}