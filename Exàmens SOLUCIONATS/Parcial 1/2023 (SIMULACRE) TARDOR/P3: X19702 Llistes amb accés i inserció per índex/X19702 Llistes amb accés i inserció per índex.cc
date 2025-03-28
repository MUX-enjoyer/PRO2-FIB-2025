#include <iostream>
using namespace std;

#include <list>

int main() {
    list<int> v;
    list<int>::iterator it = v.begin();
    string command;
    while (cin >> command) {
        if (command == "index++;") ++it;
        else if (command == "index--;") --it;
        else if (command == "v.push_front(") {
            int number;
            cin >> number;
            string ending;
            cin >> ending; // Això consumeix el ");"
            
            v.push_front(number);
            if (v.size() == 1) it = v.begin();
            else --it;
        }
        else if (command == "v.push_back(") {
            int number;
            cin >> number;
            string ending;
            cin >> ending; // Això consumeix el ");"
            
            v.push_back(number);
            if (v.size() == 1) it = v.begin();
        }
        else if (command == "v.insert(index,") {
            int number;
            cin >> number;
            string ending;
            cin >> ending; // Això consumeix el ");"
            
            v.insert(it, number);
            --it;
        }

        else if (command == "cout<<v[index]<<endl;") {
            cout << *it << endl;
        }
    }
}