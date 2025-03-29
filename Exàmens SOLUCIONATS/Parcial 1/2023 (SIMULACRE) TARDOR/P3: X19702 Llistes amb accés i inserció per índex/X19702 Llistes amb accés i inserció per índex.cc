#include <iostream>
using namespace std;

#include <list>

// NO VA

void imprimeix(list<int> l, list<int>::iterator it2, int index) {
    list<int>::iterator it;
    cout << "Llista";
    for (it = l.begin(); it != l.end(); ++it) {
        cout << " " << *it;
    }
    cout << endl << "Index " << index << *it2 << endl;
}


int main() {
    list<int> v;
    list<int>::iterator it = v.begin();
    int index = 0;
    string command;
    while (cin >> command) {
        if (command == "index++;") ++it;
        else if (command == "index--;") {
            if (v.size() == 1) {
                it = v.begin();
                index = 0;
            }
            else {
                --it;
                --index;
            }
        }
        else if (command == "v.push_front(") {
            int number;
            cin >> number;
            string ending;
            cin >> ending; // Això consumeix el ");"
            
            v.push_front(number);
            if (v.size() == 1) {
                it = v.begin();
                index = 0;
            }
            else {
                --it;
                --index;
            }
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
            --index;
        }

        else if (command == "cout<<v[index]<<endl;") {
            cout << *it << endl;
        }
       // cout << command << endl;
       // imprimeix(v, it, index);
    }
}