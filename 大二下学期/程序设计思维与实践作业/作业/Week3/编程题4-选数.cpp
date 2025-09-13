#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int ans = 0;
int num[100];
bool picked[100];

bool is_norm(int num)
{
    for (int i = 2; i <= sqrt(num); i++)
    {
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;

}

void pick_num(int n, int k,int from,int cnt)
{
    for (int i = from;i < n;i++)
    {
        if (picked[i])
        {
            continue;
        }
        else
        {
            picked[i] = true;
            cnt++;
            if (cnt == k)
            {
                int sum = 0;
                for (int j = 0;j < n;j++)
                {
                    if (picked[j])
                    {
                        sum += num[j];
                    }
                }
                if (is_norm(sum))
                {
                    ans++;
                }
            }
            pick_num(n, k, i + 1, cnt);
            picked[i] = false;
            cnt--;
        }
    }
}
void solve()
{
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
        cin >> num[i];
    }
    bool picked[n] = { false };
    pick_num(n, k, 0, 0);

    cout << ans << endl;
}

int main()
{
    solve();
    return 0;
}