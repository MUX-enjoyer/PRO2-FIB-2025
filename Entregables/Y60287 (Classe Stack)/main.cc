
using namespace std;
#include <iostream>
#include <string>
#include "vstack.hh"
#include "html_elem.hh"

int main() {
    string word;
    VStack stack;

    while (cin >> word) {
        if (is_tag(word)) {
            if (is_close_tag(word) && !stack.empty()) stack.pop();
            else {
                string name_tag = tag_name(word);
                stack.push(name_tag);
                if (name_tag == "script") {
                    cin >> word;
                    if (stack.size() >= 3 &&
                    stack.top(-1) == "head" &&
                    stack.top(-2) == "html") {
                        while (!is_tag(word)) {
                            cout << word;
                            cin >> word;
                        }
                        
                    }
                    else while (!is_tag(word)) cin >> word;
                }
                stack.pop();
            }
        }
        cout << word << " ";
    }
    cout << endl;
}