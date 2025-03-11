using namespace std;
#include <iostream>
#include <list>
#include <string>

int main() {
    list<int> llista;
    list<int>::iterator mid = llista.end();
    int x, size = 0;
    string instruccio;

    while (cin >> instruccio) {
        if (instruccio == "get_mid_value") {
            if (size % 2 == 0) cout << "error" << endl;
            else cout << *mid << endl;
        } else if (instruccio == "push_front") {
            cin >> x;
            llista.push_front(x);
            ++size;
            if (size == 1) mid = llista.begin();
            else if (size % 2 == 1) --mid;
        } else if (instruccio == "push_back") {
            cin >> x;
            llista.push_back(x);
            ++size;
            if (size == 1) mid = llista.begin();
            else if (size % 2 == 0) ++mid;
        } else if (instruccio == "pop_front") {
            if (llista.empty()) cout << "error" << endl;
            else {
                if (size % 2 == 1) ++mid;
                llista.pop_front();
                --size;
                if (size == 0) mid = llista.end();
            }
        } else if (instruccio == "pop_back") {
            if (llista.empty()) cout << "error" << endl;
            else {
                if (size % 2 == 0) --mid;
                llista.pop_back();
                --size;
                if (size == 0) mid = llista.end();
            }
        }
    }
}