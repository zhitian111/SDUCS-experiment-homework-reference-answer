#include <iostream>

using namespace std;

void solve()
{
    int n;
    cin >> n;
    char s[n];
    cin >> s;
    int m;
    cin >> m;

    int prefix[n][26];
    for (int i = 0; i < 26; i++)
    {
        prefix[0][i] = 0;
    }
    prefix[0][s[0] - 'A'] = 1;

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            prefix[i][j] = prefix[i - 1][j];
        }
        prefix[i][s[i] - 'A']++;
    }

    for (int i = 0; i < m; i++)
    {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        int count = 0;
        if (l == 0)
        {
            for (int j = 0; j < 26; j++)
            {
                if (prefix[r][j] > 0)
                {
                    count++;
                }
            }
        }
        else
        {
            for (int j = 0; j < 26; j++)
            {
                if (prefix[r][j] - prefix[l - 1][j] > 0)
                {
                    count++;
                }
            }  
        }
        if (count == 26)
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }
}
int main()
{
    solve();
    return 0;
}