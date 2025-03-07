
#include <iostream>
#include <utility>
using namespace std;

pair<int, int> divmod(int a, int b) {
    pair<int, int> parell_enters(a / b, a % b);
    return parell_enters;
}

int main() {
    int a, b;
    cin >> a >> b;
    pair<int, int> p = divmod(a, b);
    cout << p.first << ' ' << p.second << endl;
}
