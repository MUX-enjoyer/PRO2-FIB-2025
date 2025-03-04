#include <iostream>
#include <list>
#include <string>
using namespace std;

list<string>::const_iterator longest(const list<string>& v) {
    int mida_max = 0;
    list<string>::const_iterator longest_word = v.end();
    list<string>::const_iterator it;
    for (it = v.begin(); it != v.end(); ++it) {
        string paraula = *it;
        if (paraula.size() > mida_max) {
            mida_max = paraula.size();
            longest_word = it;
        }
    }
    return longest_word;
}

int main() {
    string word;
    list<string> text;
    while (cin >> word) {
        text.push_back(word);
    }
    auto i = longest(text);
    if (i != text.end()) {
        cout << *i << endl;
    } else {
        cout << "<empty sequence>" << endl;
    }
    return 0;
}
