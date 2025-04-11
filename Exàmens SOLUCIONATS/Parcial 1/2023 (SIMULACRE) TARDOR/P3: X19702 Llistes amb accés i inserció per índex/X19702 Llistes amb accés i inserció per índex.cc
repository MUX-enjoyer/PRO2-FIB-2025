#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v;
    int index = 0;
    string command;
    while (cin >> command) {
        if (command == "index++;") {
            ++index;
        }
        else if (command == "index--;") {
            --index;
        }
        else if (command == "v.push_front(") {
            int number;
            cin >> number;
            string ending;
            cin >> ending; // Això consumeix el ");"
            v.insert(v.begin(),number);
        }
        else if (command == "v.push_back(") {
            int number;
            cin >> number;
            string ending;
            cin >> ending; // Això consumeix el ");"
            v.push_back(number);
        }
        else if (command == "v.insert(index,") {
            int number;
            cin >> number;
            string ending;
            cin >> ending; // Això consumeix el ");"
            v.insert(v.begin() + index,number);
        }
        else if (command == "cout<<v[index]<<endl;") {
            cout << v[index] << endl;
        }
    }
}