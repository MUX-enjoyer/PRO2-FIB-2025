#include <iostream>
#include <list>
#include <vector>

#include "matriu.hh"

using namespace std;

// Constructora

template <typename T>
matriu<T>::matriu(int m, int n) {
    nfil = m;
    ncol = n;
    files = vector<list<parint>>(m);
    // Omplo el vector amb m llistes buides (ja que són tot zeros)
}

// Modificadora

template <typename T>
void matriu<T>::modif_pos(int i, int j, T x) {
    typename list<parint>::iterator it;
    for (it = files[i].begin(); it != files[i].end(); ++it) {
        if (it->col == j) {
            if (x != 0)
                it->val = x;
            else
                files[i].erase(it);
            return;
        }
    }
    if (x != 0) files[i].push_back({j, x});
}

// Consultores

template <typename T>
int matriu<T>::num_files() const {
    return nfil;
}

template <typename T>
int matriu<T>::num_columnes() const {
    return ncol;
}

template <typename T>
T matriu<T>::pos(int i, int j) const {
    typename list<parint>::const_iterator it;
    for (it = files[i].begin(); it != files[i].end(); ++it) {
        if (it->col == j) return it->val;
    }
    return 0;
}

// Suma de matrius

template <typename T>
void matriu<T>::suma(const matriu& m1, const matriu& m2) {
    nfil = m1.nfil;
    ncol = m1.ncol;
    files = vector<list<parint>>(nfil);

    for (int i = 0; i < nfil; ++i) {
        for (int j = 0; j < ncol; ++j) {
            T suma_val = m1.pos(i, j) + m2.pos(i, j);
            if (suma_val != 0) {
                files[i].push_back({j, suma_val});
            }
        }
    }
}

// Producte de matrius
template <typename T>
void matriu<T>::producte(const matriu& m1, const matriu& m2) {
    nfil = m1.nfil;
    ncol = m2.ncol;
    files = vector<list<parint>>(nfil);

    for (int i = 0; i < nfil; ++i) {
        for (int j = 0; j < ncol; ++j) {
            T prod_val = 0;
            for (int k = 0; k < m1.ncol; ++k) {
                prod_val += m1.pos(i, k) * m2.pos(k, j);
            }
            if (prod_val != 0) {
                files[i].push_back({j, prod_val});
            }
        }
    }
}

// Lectura

template <typename T>
void matriu<T>::llegeix(int m, int n) {
    nfil = m;
    ncol = n;
    files = vector<list<parint>>(m);

    for (int i = 0; i < m; ++i) {
        int num_elements;
        cin >> num_elements;
        for (int j = 0; j < num_elements; ++j) {
            int col;
            T val;
            cin >> col >> val;
            files[i].push_back({col, val});
        }
    }
}

// Escriptura

template <typename T>
void matriu<T>::escriu() const {
    for (int i = 0; i < nfil; ++i) {
        typename list<parint>::const_iterator it = files[i].begin();
        for (int j = 0; j < ncol; ++j) {
            if (it != files[i].end() && it->col == j) {
                cout << it->val << " ";
                ++it;
            } else {
                cout << "0 ";
            }
        }
        cout << endl;
    }
    cout << endl;
}
