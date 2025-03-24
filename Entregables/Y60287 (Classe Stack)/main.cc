
using namespace std;
#include <iostream>
#include <string>
#include "vstack.hh"
#include "html_elem.hh"

int main() {
    string word;
    VStack stack;
    bool in_script = false;
    bool keep_script_content = false;

    while (cin >> word) {
        if (is_tag(word)) {
            bool close_tag = is_close_tag(word);
            string name_tag = tag_name(word);

            if (!close_tag) { //Obre
                stack.push(name_tag);
                if (name_tag == "script") {
                    in_script = true;
                    // Comprovem si estem en l'excepció: script dins head dins html
                    keep_script_content =
                        (stack.top(-1) == "head" &&
                        stack.top(-2) == "html");
                }
            } else {
                if (!stack.empty() && stack.top(0) == name_tag) {
                    stack.pop();
                }
                if (name_tag == "script") {
                    in_script = false;
                    keep_script_content = false;
                }
            }
            cout << word << " ";
        } else {
            // Si estem dins d'un script i no s'ha de conservar el contingut, ignorem el text
            if (!in_script || keep_script_content) {
                cout << word << " ";
            }
        }
    }
    cout << endl;
}