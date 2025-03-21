#ifndef INLINE_HH
#define INLINE_HH

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include "bintree.hh"

template <typename T>
class BinTreeInlineReader {
    std::string line_;
    int i_;

    T parse_value_(std::string token) const;
    std::string read_token_();
    pro2::BinTree<T> read_delimited_(char delimiter);
    pro2::BinTree<T> read_();

 public:
    BinTreeInlineReader(std::string line) : line_(line), i_(0) {}

    pro2::BinTree<T> read();
};

template <typename T>
std::string BinTreeInlineReader<T>::read_token_() {
    int start = i_;
    while (i_ < line_.size()) {
        const char c = line_[i_];
        if (c == ',' || c == '(' || c == ')') {
            break;
        }
        i_++;
    }
    return line_.substr(start, i_ - start);
}

template <typename T>
T BinTreeInlineReader<T>::parse_value_(std::string token) const {
    std::istringstream iss(token);
    T value;
    iss >> value;
    return value;
}

template <typename T>
pro2::BinTree<T> BinTreeInlineReader<T>::read_delimited_(char delimiter) {
    auto t = read_();
    if (line_[i_] != delimiter) {
        throw std::runtime_error("Unexpected character");
    }
    i_++;
    return t;
}

// El empty debe estar delimitado
template <typename T>
pro2::BinTree<T> BinTreeInlineReader<T>::read_() {
    std::string token = read_token_();
    if (token.empty()) {
        return pro2::BinTree<T>();
    }
    T value = parse_value_(token);
    if (line_[i_] != '(') {
        return pro2::BinTree<T>(value);
    }
    i_++;
    auto left = read_delimited_(',');
    auto right = read_delimited_(')');
    return pro2::BinTree<T>(value, left, right);
}

template <typename T>
pro2::BinTree<T> BinTreeInlineReader<T>::read() {
    try {
        pro2::BinTree<T> t = read_();
        if (i_ != line_.size()) {
            throw std::runtime_error("Expected to reach end of input");
        }
        return t;
    } catch (const std::runtime_error& e) {
        std::cerr << "Format error!" << std::endl;
        return pro2::BinTree<T>();
    }
}

template <typename T>
pro2::BinTree<T> bintree_inline_read(std::string line) {
    return BinTreeInlineReader<T>(line).read();
}

#endif