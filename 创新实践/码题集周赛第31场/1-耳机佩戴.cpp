#include <algorithm>
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int a, b;
        std::cin >> a >> b;
        ans += std::min(a, b);
    }
    std::cout << ans << '\n';
    return 0;
}
