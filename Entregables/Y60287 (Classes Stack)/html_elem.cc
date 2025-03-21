#include "html_elem.hh"
#include <cassert>
using std::string;

bool is_tag(string s) {
    // 3 -> shortest tag name is 1 char long
    return s.size() >= 3 && s[0] == '<' && s[s.size() - 1] == '>';
}

bool is_close_tag(string s) {
    return is_tag(s) && s[1] == '/';
}

string tag_name(string s) {
    assert(is_tag(s));
    bool closing = s[1] == '/';
    int  start = closing ? 2 : 1;
    int  size = s.size() - (closing ? 3 : 2);
    return s.substr(start, size);
}