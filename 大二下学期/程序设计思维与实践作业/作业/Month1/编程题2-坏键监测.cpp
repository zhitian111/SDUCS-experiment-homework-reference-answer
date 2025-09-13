#include <iostream>
#include <string>
using namespace std;


bool is_broken(string s)
{
    // if (!((s[s.length() - 1] >= 'a' && s[s.length() - 1] <= 'z') || (s[s.length() - 1] >= 'A' && s[s.length() - 1] <= 'Z')))
    // {
    //     return false;
    // }
    
    for (int i = 0;i < s.length() - 1;i++)
    {
        if (s[i] == s[i + 1])
        {
            return true;
        }
    }

    int count[26];
    bool cap = false;
    for (int i = 0;i < 26;i++)
    {
        count[i] = 0;
    }

    for (auto c : s)
    {
        if (c >= 'a' && c <= 'z')
        {
            count[c - 'a']++;
        }
        if (c >= 'A' && c <= 'Z')
        {
            count[c - 'A']++;
            cap = true;
        }
    }

    for (int i = 0;i < 26;i++)
    {
        if (count[i] == 0)
        {
            return true;
        }
    }

    if (!cap)
    {
        return true;
    }

    return false;
}

void solve()
{
    int n;
    cin >> n;
    for (int i = 0;i < n;i++)
    {
        string s;
        cin >> s;
        if (is_broken(s))
        {
            cout << "yes" << endl;
        }
        else
        {
            cout << "no" << endl;
        }
    }
}

int main()
{
    solve();
    return 0;
}