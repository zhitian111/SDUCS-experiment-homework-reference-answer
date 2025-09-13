#include <iostream>

using namespace std;

void solve()
{
    int n, k;
    cin >> n >> k;
    int cnt[k] = {0};
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        cnt[x - 1]++;
    }
    int ans = 0;
    for (int i = 0; i < k; i++)
    {
        ans += cnt[i] / 2;
    }
    
    // 如果穿颜色不同的，那计算方式是下边这种
    // int cnt1 = 0, cnt2 = 0;
    // for (int i = 0; i < k; i++)
    // {
    //     if (cnt1 <= cnt2)
    //     {
    //         cnt1 += cnt[i];
    //         continue;
    //     }
    //     if (cnt2 < cnt1)
    //     {
    //         cnt2 += cnt[i];
    //         continue;
    //     }
    // }
    // cout << min(cnt1, cnt2);
    cout << ans;
}


int main()
{
    solve();
    return 0;
}