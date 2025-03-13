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

    for (const auto parell : fruites) {
        cout << parell.first << " " << parell.second << endl;
    }

}
