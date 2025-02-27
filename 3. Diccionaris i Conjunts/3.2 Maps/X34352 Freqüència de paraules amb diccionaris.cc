#include <iostream>
using namespace std;

#include <string>
#include <map>

int main() {
    map<string, int> partits;
    string codi, paraula;
    while(cin >> codi >> paraula) {
        if (codi == "a") ++partits[paraula];
        else if (codi == "f") cout << partits[paraula] << endl;
    }
}