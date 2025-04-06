#include <iostream>
#include <string>
#include <vector>
using namespace std;

class balloon
{
public:
    int price;
    string code;
    bool enable;
    balloon();
};

balloon::balloon()
{
    cin >> price;
    cin >> code;
    int cnt[10] = {0};
    for (auto& c : code)
    {
        cnt[c - '0']++;
    }
    if (cnt[0] >= 2 && cnt[5] >= 1 && cnt[1] >= 1)
    {
        enable = true;
    }
    else
    {
        enable = false;
    }
}

void solve()
{
    int n;
    cin >> n;
    vector<balloon> bs;
    for (int i = 0; i < n; i++)
    {
        balloon b;
        bs.push_back(b);
    }
    int min_price = 1e9;
    int ans = 0;
    for (int i = 0; i < bs.size(); i++)
    {
        if (bs[i].enable)
        {
            if (bs[i].price < min_price)
            {
                min_price = bs[i].price;
                ans = i + 1;
            }
        }
    }
    cout << ans;
}

int main()
{
    solve();
    return 0;
}