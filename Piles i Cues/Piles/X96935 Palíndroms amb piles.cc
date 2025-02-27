#include <iostream>
using namespace std;

#include <stack>

bool palindrom(stack<int> s, int n) {
    int x;
    if (n%2 != 0) cin >> x;
    for (int i = 0; i < n/2; ++i) {
        cin >> x;
        if (s.top() != x) return false;
        s.pop();
    }
    return true;
}

int main() {
    int n;
    stack<int> nums;
    cin >> n;
    for (int i = 0; i < n/2; ++i) {
        int a;
        cin >> a;
        nums.push(a);
    }
    if(palindrom(nums, n)) cout << "SI" << endl;
    else cout << "NO" << endl;
}