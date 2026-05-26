#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, v;
    cin >> n >> v;
    bool p = false;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        if (s == "Press") {
            if (p || v <= 0) {
                cout << "Error\n";
                return 0;
            }
            p = true;
            v--;
        } else if (s == "Continue") {
            if (!p) {
                cout << "Error\n";
                return 0;
            }
            v--;
            if (v < 0) {
                cout << "Error\n";
                return 0;
            }
        } else {
            if (!p) {
                cout << "Error\n";
                return 0;
            }
            p = false;
        }
    }
    cout << v << "\n";
    return 0;
}
