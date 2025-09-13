#include <iostream>
#include <string>
using namespace std;

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    string ans;
    bool mark = false;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u')
        {
            if (mark == false)
            {
                mark = true;
                ans += s[i];
            }
        }
        else
        {
            mark = false;
            ans += s[i];
        }
    }
    cout << ans << endl;
}

int main()
{
    solve();
    return 0;
}