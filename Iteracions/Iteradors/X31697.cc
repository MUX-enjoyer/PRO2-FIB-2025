#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

void inserta_don(vector<string>& frase) {
    vector<string>::iterator it;
    for (it = frase.begin(); it != frase.end(); ++it) {
        if (*it == "Camilo") {
            it = frase.insert(it, "Don");
            ++it;
        }
    }
}

int main() {
   string p;
   vector<string> frase;
   while (cin >> p) frase.push_back(p);
   inserta_don(frase);
   copy(frase.begin(), frase.end(),
        ostream_iterator<string>(cout, " "));
   cout << endl;
}


