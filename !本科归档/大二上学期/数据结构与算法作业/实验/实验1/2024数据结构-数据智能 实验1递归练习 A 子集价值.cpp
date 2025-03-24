/*2024数据结构-数据智能 实验1递归练习 A 子集价值.cpp*/
#include <iostream>
using namespace std;
class Solution {
public:
    int ans = 0;
    void SubSetValue(int a[], int mark[], int n, int m)
    {
    if (m == n)
    {
        int cnt = 1;
        int sum = 0;
        for (size_t i = 0; i < n;i++)
        {
            sum = sum + cnt * a[i] * mark[i];
            cnt = cnt + mark[i];
        }
        ans = ans ^ sum;
    }
        if (m != n)
        {
            mark[m] = 0;
            SubSetValue(a,mark, n, m + 1);
            mark[m] = 1;
            SubSetValue(a,mark, n, m + 1);
        }
    }
    void solute()
    {
        int n;
        cin >> n;
        int a[n];
        for (size_t i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        int mark[n];
        for (size_t i = 0;i < n;i++)
        {
            mark[i] = 1;
        }
        SubSetValue(a,mark, n, 0);
        cout << ans;
        }
};

int main()
{
    Solution ans;
    ans.solute();
    return 0;
}