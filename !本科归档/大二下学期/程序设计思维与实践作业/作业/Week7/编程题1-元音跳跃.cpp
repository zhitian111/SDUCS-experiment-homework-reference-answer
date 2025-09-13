#include <iostream>
#include <string>
using namespace std;

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    int best = 0;
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u')
        {
            count++;
        }
        else
        {
            best = max(best, count);
            count = 0;
        }
    }
    cout << best << endl;
}

int main()
{
    solve();
    return 0;
}