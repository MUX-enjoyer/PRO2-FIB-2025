using namespace std;
#include <iostream>
#include <set>
#include <string>
#include <map>

struct info {
    set<string> webs;
    int ultim_acces;
    int n_accessos = 1;
    bool esBot = false;
};


int main() {
    map<string, info> log;

    string IP, web;
    int temps;

    while (cin >> IP >> web >> temps) {
        map<string, info>::iterator it = log.find(IP);
        if (it == log.end()) {
            info nova_IP;
            nova_IP.ultim_acces = temps;
            nova_IP.webs = {web};
            log.insert({IP, nova_IP});
        }
        else {
            it->second.webs.insert(web);
            if (temps - it->second.ultim_acces <= 100) {
                ++it->second.n_accessos;
                if (it->second.n_accessos >= 20) {
                    it->second.esBot = true;
                }
            }
            else it->second.n_accessos = 1;

            it->second.ultim_acces = temps;
        }
    }

    map<string, info>::iterator it;
    for (it = log.begin(); it != log.end(); ++it) {
        if (it->second.esBot) {
            cout << it->first;
            set<string>::iterator it2;
            for (it2 = it->second.webs.begin(); it2 != it->second.webs.end(); ++it2) {
                cout << " " << *it2;
            }
            cout << endl;
        }
    }
}