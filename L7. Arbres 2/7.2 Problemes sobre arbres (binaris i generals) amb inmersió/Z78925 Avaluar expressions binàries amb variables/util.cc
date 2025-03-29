#include "util.hh"
#include <sstream>
#include <cassert>
using namespace std;

bool is_number(string s) {
    if (s.empty()) {
        return false;
    }
    for (char c : s) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool is_var_name(string s) {
    if (s.empty()) {
        return false;
    }
    for (char c : s) {
        if (!isalpha(c)) {
            return false;
        }
    }
    return true;
}

int string_to_int(string s) {
    istringstream iss(s);
    int x = 0;
    iss >> x;
    assert(!iss.fail());
    return x;
}
