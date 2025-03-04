#include <iostream>
#include <vector>
#include <string>
#include <iterator>
using namespace std;

struct Player { 
    string name; 
    int score;
};a

vector<string> winners(vector<Player>::iterator ini, vector<Player>::iterator fin) {
    vector<string> winners;
    int max_punt = ini->score;
    for (vector<Player>::iterator it = ini; it != fin; ++it) {
        if (it->score == max_punt) {
            winners.push_back(it->name);
        }
        else if (it->score > max_punt) {
            max_punt = it->score;
            winners.clear();
            winners.push_back(it->name);
        }
    }
    return winners;
}

int main() {
   Player p;
   vector<Player> v;
   while (cin >> p.name >> p.score) {
      v.push_back(p);
   }
   vector<string> w = winners(v.begin(), v.end());
   for (int i = 0; i < w.size(); i++) {
      cout << (i == 0 ? "" : " ") << w[i];
   }
   cout << endl;
}