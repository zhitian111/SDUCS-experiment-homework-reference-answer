#include <iostream>
#include <limits>
using namespace std;

void solve()
{
    int n;
    cin >> n;
    char s[n];
    cin >> s;
    int left = 0;
    int right = 0;
    int count = 0;
    int flags[26] = { 0 };
    int best = numeric_limits<int>::max();

    while (right < n)
    {

        flags[s[right] - 'A']++;
        if (flags[s[right] - 'A'] == 1)
        {
            count++;            
        }
        while (count == 26)
        {
            best = min(best, right - left + 1);
            if (flags[s[left] - 'A'] >= 1)
            {
                flags[s[left] - 'A']--;
                if (flags[s[left] - 'A'] == 0)
                {
                    count--;
                }
            }
            left++;
        }
        right++;
    }

    cout << best<< endl;
}

int main()
{
    solve();
    return 0;
}