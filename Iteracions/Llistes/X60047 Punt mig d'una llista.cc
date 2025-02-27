using namespace std;
#include <iostream>

#include <string>
#include <list>

int main() {
    list<int> llista;
    int x, mid;
    bool canvi_mid = true;

    string instruccio;
    while (cin >> instruccio) {
        if (instruccio == "get_mid_value") {
            if (llista.size()%2 == 0 || llista.empty()) cout << "error" << endl;
            else {
                if (canvi_mid) {
                    if (llista.size() == 1) mid = llista.front();
                    else {
                        list<int>::iterator it = llista.begin();
                        for (int i = 0; i < llista.size()/2; ++i) ++it;
                        mid = *it;
                    }
                    canvi_mid = false;
                }
                cout << mid << endl;
            }
        }
        else {
            if (instruccio == "push_front") {
                cin >> x;
                llista.push_front(x);
            }
            else if (instruccio == "push_back") {
                cin >> x;
                llista.push_back(x);
            }
            else if (instruccio == "pop_front") {
                if (llista.empty()) cout << "error" << endl;
                else llista.pop_front();
            }
            else if (instruccio == "pop_back") {
                if (llista.empty()) cout << "error" << endl;
                else llista.pop_back();
            }
            canvi_mid = true;
        }
    }
}