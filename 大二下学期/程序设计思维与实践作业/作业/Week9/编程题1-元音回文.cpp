#include <iostream>
#include <algorithm>
using namespace std;

inline bool is_meta_vowel(char c)
{
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

void solve()
{
    size_t n;
    cin >> n;
    char s[n + 1];
    cin >> s;
    size_t ans = 0;
    size_t tem = 0;
    for (size_t i = 0; i < n; i++)
    {
        auto left = i - 1;
        auto right = i + 1;
        if (left >= 0 && right < n && (s[i] == s[right] || (is_meta_vowel(s[i]) && is_meta_vowel(s[right]))))
        {
            tem++;
            right++;
            while (left >= 0 && right < n && (s[left] == s[right] || (is_meta_vowel(s[left]) && is_meta_vowel(s[right]))))
            {
                left--;
                right++;
                tem++;
            }
            ans = max(ans, tem * 2);
            tem = 0;
        }
        left = i - 1;
        right = i + 1;
        while (left >= 0 && right < n && (s[left] == s[right] || (is_meta_vowel(s[left]) && is_meta_vowel(s[right]))))
        {
            left--;
            right++;
            tem++;
        }
        
        ans = max(ans, tem * 2 + 1);
        tem = 0;
    }
    cout << ans << endl;
}
int main()
{
    solve();
    return 0;
}