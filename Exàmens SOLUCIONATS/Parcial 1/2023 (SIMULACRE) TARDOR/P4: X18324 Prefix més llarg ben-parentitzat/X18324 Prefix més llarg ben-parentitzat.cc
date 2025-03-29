#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    string line;

    while (cin >> line) {
        stack<char> s;

        int last_empty_stack = 0; //pos 0 està¡ ben parentitzada
        int n = line.size();
        int i = 0; //iterador
        bool ben_par = true; //supusem true
        while(ben_par and i < n) {
            if (not s.empty()) {
                if (line[i] == '(' or line [i] == '[') s.push(line[i]);

                else if (line[i] == ')') {
                    if (s.top() == '(') s.pop();
                    else ben_par = false;
                }

                else {
                    if (s.top() == '[') s.pop();
                    else ben_par = false;
                }

                if (s.empty()) last_empty_stack = i + 1;
            }

            else {
                if (line[i] == '(' or line [i] == '[') s.push(line[i]);
                else ben_par = false;
            }
            ++i;
        }

        cout << last_empty_stack << endl;
    }
}