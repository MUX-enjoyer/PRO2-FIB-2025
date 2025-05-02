#include <iostream>
#include <map>
using namespace std;

int main() {
    map<string, int> fruites;
    string fruita;
    int quantitat;

    while (cin >> fruita >> quantitat) {
        fruites[fruita] += quantitat;
    }

    map<string, int>::iterator it;
    for (it = fruites.begin(); it != fruites.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
}
