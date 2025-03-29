#ifndef VECTOR_IO_HH
#define VECTOR_IO_HH

#include <vector>
#include <iostream>

template <typename T>
void print_vector(const std::vector<T>& v) {
    std::cout << "[";
    if (!v.empty()) {
        std::cout << v[0];
        for (int i = 1; i < v.size(); ++i) {
            std::cout << "," << v[i];
        }
    }
    std::cout << "]" << std::endl;
}

#endif