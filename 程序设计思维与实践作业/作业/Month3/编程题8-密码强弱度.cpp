#include <bits/stdc++.h>
using namespace std;
template<typename T> inline void __debug__(T x, string name)
{
    cerr << name << " = " << x << endl;
}
template<typename T> inline void __debug__(T* x, string name, size_t size)
    {
    cerr << name << "[" << size << "] = ";
    for (size_t i = 0; i < size; i++)
    {
        cerr << x[i] << " ";
    }
    cerr << endl;
}
#define debug(x) __debug__(x, (#x));
#define adebug(x) __debug__(x, (#x), sizeof(x)/sizeof(x[0]));
void solve()
{
    string s;
    cin >> s;
    if (s.size() < 6)
    {
        cout << 0 << endl;
        return;
    }
    size_t start = 0;
    size_t ans = 0;
    while (start < s.size())
    {
        if (s[start] >= '0' && s[start] <= '9')
        {
            start = s.find_first_not_of("0123456789", start + 1);
            ans++;
        }
        else if (s[start] >= 'a' && s[start] <= 'z')
        {
            start = s.find_first_not_of("abcdefghijklmnopqrstuvwxyz", start + 1);
            ans++;
        }
        else if (s[start] >= 'A' && s[start] <= 'Z')
        {
            start = s.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ", start + 1);
            ans++;
        }
    }
    cout << ans << endl;
}
int main()
{
    solve();
    return 0;
}