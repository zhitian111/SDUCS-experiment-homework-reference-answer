#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<string> g(n);
    for (int i = 0; i < n; i++) cin >> g[i];
    static const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    static const int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    unordered_set<string> st;
    st.reserve(n * n * 8 * n / 2);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int d = 0; d < 8; d++) {
                string s;
                for (int x = i, y = j; x >= 0 && x < n && y >= 0 && y < n; x += dx[d], y += dy[d]) {
                    s.push_back(g[x][y]);
                    st.insert(s);
                }
            }
        }
    }
    cout << st.size() << '\n';
    return 0;
}
