#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    string line;

    while (cin >> line) {
        stack<char> s;
        int pos_ben_parentitzada = 0;
        bool ben_parentitzada = true;
        for (int i = 0; ben_parentitzada && i < line.size(); ++i) {
            char c = line[i];
            if (s.empty()) {
                if (c == '(' or c == '[') s.push(c);
                else ben_parentitzada = false;
            }
            else {
                if (c == '(' or line [i] == '[') s.push(c);
                else if ((c == ')' && s.top() == '(') || (c == ']' && s.top() == '[')) {
                    s.pop();
                    if (s.empty()) pos_ben_parentitzada = i+1;
                }
                else ben_parentitzada = false;
            }
        }
        cout << pos_ben_parentitzada << endl;
    }
}