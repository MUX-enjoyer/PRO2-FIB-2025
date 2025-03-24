#include "vstack.hh"
#include <cassert>
using std::string;

void VStack::push(string s) {
    stack_.push_back(s);
}

void VStack::pop() {
    stack_.pop_back();
}

size_t VStack::size() const {
    return stack_.size();
}

bool VStack::empty() const {
    return stack_.empty();
}

string VStack::top(int depth) const {
    int i = stack_.size() - 1 + depth;
    assert(i >= 0 && i < int(stack_.size()));
    return stack_[i];
}

bool VStack::contains(string s) const {
    for (const string& elem : stack_) {
        if (elem == s) {
            return true;
        }
    }
    return false;
}