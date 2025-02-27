using namespace std;
#include <iostream>

#include <list>

int min_max(const list<int>& l, int epsilon) {
    int min_max = *l.begin();
    for (list<int>::const_iterator it = l.begin(); it != l.end(); ++it) {
        if (min_max * epsilon < *it * epsilon) min_max = *it;
    }
    return min_max;
}

void borra(list<int>& llista, float& suma, int n) {
    for (list<int>::iterator it = llista.begin(); it != llista.end(); ++it) {
        if (*it == n) {
            llista.erase(it);
            suma -= n;
            return;
        }
    }
}

int main() {
    list<int> llista;
    int codi, n, min, max;
    min = max = 0;
    float suma = 0;
    bool primer = true;
    cin >> codi >> n;
    while (n != 0 || codi != 0) {
        if (codi == -1) {
            if (primer) {
                suma = 0;
                min = n;
                max = n;
            }
            else if (n < min) min = n;
            else if (n > max) max = n;
            llista.push_back(n);
            suma += n;
        }
        else if (!llista.empty() && codi == -2) {
            borra(llista, suma, n);
            if (min == n) min = min_max(llista, -1);
            else if (max == n) max = min_max(llista, 1);
        }
        
        if (llista.empty()) {
            primer = true;
            cout << 0 << endl;
        }
        else {
            cout << min << ' ' << max << ' ' << suma/llista.size() << endl;
            primer = false;
        }
        cin >> codi >> n;
    }
}