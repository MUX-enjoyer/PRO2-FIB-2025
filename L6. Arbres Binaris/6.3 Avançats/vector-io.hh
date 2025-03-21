#ifndef VECTOR_IO_HH
#define VECTOR_IO_HH

#include <vector>

template <typename T>
void print_vector(const std::vector<T>& v) {
    cout << "[";
    if (!v.empty()) {
        cout << v[0];
        for (int i = 1; i < v.size(); ++i) {
            cout << "," << v[i];
        }
    }
    cout << "]" << endl;
}

#endif