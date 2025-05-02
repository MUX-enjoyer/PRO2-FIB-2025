#include <iostream>
using namespace std;

#include <queue>

void min_max(queue<int> c, int& min, int& max) {
    min = max = c.front();
    c.pop();
    while (!c.empty()) {
        if (c.front() < min) min = c.front();
        else if (c.front() > max) max = c.front();
        c.pop();
    }
}

int main() {
    queue<int> cua;
    int n, min, max;
    cin >> n;
    double suma = 0;
    min = max = n;
    while (n <= 1000 && n >= -1001) {
        if (n != -1001) {
            if (n < min) min = n;
            else if (n > max) max = n;
            suma += n;
            cua.push(n);
        }
        else if (!cua.empty()) {
            int num_abans = cua.front();
            suma -= num_abans;
            cua.pop();
            if (!cua.empty() && (min == num_abans || max == num_abans)) min_max(cua, min, max);
        }
        
        if (cua.empty()) {
            int min = 1001;
            int max = -1001;
            suma = 0;
            cout << 0;
        }
        else cout << "min " << min << "; max " << max << "; media " << suma/cua.size();
        cout << endl;
        cin >> n;
    }
}