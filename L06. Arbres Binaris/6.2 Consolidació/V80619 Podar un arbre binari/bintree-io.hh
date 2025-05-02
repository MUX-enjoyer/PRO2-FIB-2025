#ifndef BINTREE_IO_HH
#define BINTREE_IO_HH

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include "bintree.hh"

namespace pro2 {

enum Pieces {
    none = -1,
    through = 0,
    fork = 1,
    corner = 2,
    empty = 3,
};

static constexpr const char *__thru__ = "|   ";
static constexpr const char *__fork__ = "|-- ";
static constexpr const char *__crnr__ = "'-- ";
static constexpr const char *__emty__ = "    ";

static constexpr const int   NUM_PIECES = 4;
static constexpr const int   PIECE_LENGTH = 4;
static constexpr const char *pieces[NUM_PIECES] = {
    __thru__,
    __fork__,
    __crnr__,
    __emty__,
};

template <typename T>
class BinTreeReader {
    std::istream& in_;
    std::string   line_;
    bool          error_ = false;
    bool          skip_next_getline_ = false;

    static bool only_spaces_(std::string s) {
        return std::all_of(s.begin(), s.end(), isspace);
    }

    BinTree<T> fail_() {
        in_.setstate(std::ios::failbit);
        return BinTree<T>();
    }

    void getline_() {
        if (skip_next_getline_) {
            skip_next_getline_ = false;
        } else {
            getline(in_, line_);
        }
    }

    T read_value_(std::string s) {
        std::istringstream iss(s);

        T    t;
        bool read_ok = bool(iss >> t);
        iss.get();  // Force reading after to set eof bit
        bool read_all = iss.eof();
        error_ = !read_ok || !read_all;
        return t;
    }

    BinTree<T> parse_tree_(std::string expected_prefix1 = "", std::string expected_prefix2 = "") {
        assert(expected_prefix1.size() == expected_prefix2.size());
        const int prefix_size = expected_prefix1.size();

        if (in_.eof()) {
            return fail_();
        }

        // Header
        if (line_.substr(0, prefix_size) != expected_prefix1) {
            return fail_();
        }
        std::string content = line_.substr(prefix_size);
        if (content == "#") {
            return BinTree<T>();
        }

        T value = read_value_(content);
        if (error_) {
            return fail_();
        }

        // Left child
        getline_();
        if (line_.substr(0, prefix_size) != expected_prefix2 ||
            line_.substr(prefix_size, PIECE_LENGTH) != __fork__) {
            skip_next_getline_ = true;
			return BinTree<T>(value);
        }
        auto left = parse_tree_(expected_prefix2 + __fork__, expected_prefix2 + __thru__);
        if (in_.fail()) {
            return BinTree<T>();
        }

        // Right child
        getline_();
        if (line_.substr(0, prefix_size) != expected_prefix2 ||
            line_.substr(prefix_size, PIECE_LENGTH) != __crnr__) {
            return fail_();
        }
        auto right = parse_tree_(expected_prefix2 + __crnr__, expected_prefix2 + __emty__);
        if (in_.fail()) {
            return BinTree<T>();
        }

        return BinTree<T>(value, left, right);
    }

 public:
    BinTreeReader(std::istream& in) : in_(in), error_(false) {
        // NOTE(pauek): The first line read should have some content, so skip
        // any empty lines.
        getline_();
        while (!in_.eof() && only_spaces_(line_)) {
            getline_();
        }
    }

    BinTree<T> read_tree() {
        auto tree = parse_tree_();
        getline_();
        if (!line_.empty()) {
            return fail_();
        }
        return tree;
    }
};

template <typename T>
std::istream& operator>>(std::istream& i, BinTree<T>& tree) {
    BinTreeReader<T> reader(i);
    tree = reader.read_tree();
    return i;
}

template <typename T>
class BinTreeWriter {
    std::ostream& out_;

 public:
    BinTreeWriter(std::ostream& out) : out_(out) {}

    void write2(BinTree<T> tree, std::string prefix1 = "", std::string prefix2 = "") {
        if (tree.empty()) {
            out_ << prefix1 << "#" << std::endl;
            return;
        }
        out_ << prefix1 << tree.value() << std::endl;
        if (!tree.left().empty() || !tree.right().empty()) {
            write2(tree.left(), prefix2 + __fork__, prefix2 + __thru__);
            write2(tree.right(), prefix2 + __crnr__, prefix2 + __emty__);
        }
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& o, BinTree<T> tree) {
    BinTreeWriter<T> writer(o);
    writer.write2(tree);
    o << std::endl;
    return o;
}

}  // namespace pro2

#endif