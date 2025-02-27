
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

void inserta_don(vector<string>& frase) {
    vector<string>::iterator it = frase.begin();
    for (int i = 0; i < frase.size(); ++i) {
        if (frase[i] == "Camilo") {
            frase.insert(it+i, "Don");
            ++i;
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


