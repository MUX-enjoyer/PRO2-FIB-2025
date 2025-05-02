#ifndef TREE_IO_HH
#define TREE_IO_HH

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include "tree.hh"

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
class TreeReader {
    std::istream& in_;
    std::string   line_;
    bool          error_ = false;
    bool          skip_next_getline_ = false;

    static bool only_spaces_(std::string s) {
        for (char c : s) {
            if (!isspace(c)) {
                return false;
            }
        }
        return true;
    }

    Tree<T> fail_() {
        in_.setstate(std::ios::failbit);
        return Tree<T>();
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

    Tree<T> parse_tree_(std::string expected_prefix1 = "", std::string expected_prefix2 = "") {
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
            return Tree<T>();
        }

        T value = read_value_(content);
        if (error_) {
            return fail_();
        }

        std::vector<Tree<T>> children;

        // Children except last
        getline_();
        while (line_.substr(0, prefix_size) == expected_prefix2 &&
               line_.substr(prefix_size, PIECE_LENGTH) == __fork__) {
            const auto child =
                parse_tree_(expected_prefix2 + __fork__, expected_prefix2 + __thru__);
            if (in_.fail()) {
                return Tree<T>();
            }
            children.push_back(child);
            getline_();
        }

        // Last child
        if (line_.substr(0, prefix_size) != expected_prefix2 ||
            line_.substr(prefix_size, PIECE_LENGTH) != __crnr__) {
            if (children.empty()) {
                skip_next_getline_ = true;
                return Tree<T>(value);
            }
            return fail_();
        }
        const auto child = parse_tree_(expected_prefix2 + __crnr__, expected_prefix2 + __emty__);
        if (in_.fail()) {
            return Tree<T>();
        }
        children.push_back(child);

        return Tree<T>(value, children);
    }

 public:
    TreeReader(std::istream& in) : in_(in), error_(false) {
        // NOTE(pauek): The first line read should have some content, so skip
        // any empty lines.
        getline_();
        while (!in_.eof() && only_spaces_(line_)) {
            getline_();
        }
    }

    Tree<T> read_tree() {
        auto tree = parse_tree_();
        getline_();
        if (!line_.empty()) {
            return fail_();
        }
        return tree;
    }
};

template <typename T>
std::istream& operator>>(std::istream& i, Tree<T>& tree) {
    TreeReader<T> reader(i);
    tree = reader.read_tree();
    return i;
}

template <typename T>
class TreeWriter {
    std::ostream& out_;

 public:
    TreeWriter(std::ostream& o) : out_(o) {}

    void write(Tree<T> tree, std::string prefix1 = "", std::string prefix2 = "") {
        if (tree.empty()) {
            out_ << prefix1 << "#" << std::endl;
            return;
        }
        out_ << prefix1 << tree.value() << std::endl;
        for (int i = 0; i < tree.num_children() - 1; i++) {
            write(tree.child(i), prefix2 + __fork__, prefix2 + __thru__);
        }
        if (tree.num_children() > 0) {
            Tree<T> last = tree.child(tree.num_children() - 1);
            write(last, prefix2 + __crnr__, prefix2 + __emty__);
        }
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& o, Tree<T> tree) {
    TreeWriter<T> writer(o);
    writer.write(tree);
    o << std::endl;
    return o;
}

}  // namespace pro2

#endif