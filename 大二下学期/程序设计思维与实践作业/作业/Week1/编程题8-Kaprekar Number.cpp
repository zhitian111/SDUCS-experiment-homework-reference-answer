#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>


using namespace std;

int g1(int n)
{
    vector<int> digits;
    while (n > 0)
    {
        digits.push_back(n % 10);
        n /= 10;
    }
    sort(digits.begin(), digits.end());
    int ans = 0;
    while (!digits.empty())
    {
        ans += digits.back() * pow(10, digits.size() - 1);
        digits.pop_back();
    }
    return ans;
}

int g2(int n)
{
    vector<int> digits;
    while (n > 0)
    {
        digits.push_back(n % 10);
        n /= 10;
    }
    sort(digits.begin(), digits.end());
    int ans = 0;
    while (!digits.empty())
    {
        ans += digits.front() * pow(10, digits.size() - 1);
        digits.erase(digits.begin());
    }
    return ans;
}

inline int f(int n)
{
    return g1(n) - g2(n);
}

void solve()
{
    int n, k;
    cin >> n >> k;
    // cout << g1(n) << endl;
    // cout << g2(k) << endl;
    for (int i = 0;i < k;i++)
    {
        n = f(n);
    }
    cout << n;
}

int main()
{
    solve();
    return 0;
}