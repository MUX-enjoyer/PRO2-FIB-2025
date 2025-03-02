using namespace std;
#include <iostream>
#include <list>

void min_max(const list<int>& l, int& min, int& max) {
    list<int>::const_iterator it = l.begin();
    min = max = *it;
    for (++it; it != l.end(); ++it) {
        if (min > *it)
            min = *it;
        else if (max < *it)
            max = *it;
    }
}

void borra(list<int>& llista, float& suma, int n, int& size) {
    for (list<int>::iterator it = llista.begin(); it != llista.end(); ++it) {
        if (*it == n) {
            llista.erase(it);
            --size;
            suma -= n;
            return;
        }
    }
}

int main() {
    list<int> llista;
    int codi, n, min, max;
    float suma = 0;
    int size = 0;
    cin >> codi >> n;
    min = max = n;
    while (n != 0 || codi != 0) {
        if (codi == -1) {
            if (size == 0) {
                min = n;
                max = n;
            } else if (n < min)
                min = n;
            else if (n > max)
                max = n;
            llista.push_back(n);
            ++size;
            suma += n;
        } else if (!llista.empty() && codi == -2) {
            borra(llista, suma, n, size);
            if (!llista.empty() && (min == n || max == n)) min_max(llista, min, max);
        }

        if (llista.empty()) {
            cout << 0 << endl;
            suma = 0;

        } else
            cout << min << ' ' << max << ' ' << suma / size << endl;
        cin >> codi >> n;
    }
}