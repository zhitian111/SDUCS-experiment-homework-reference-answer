#include <iostream>
#include <algorithm>
using namespace std;

void solve()
{
    struct time_snip
    {
        double start, end;
    };
    
    size_t n;
    cin >> n;
    time_snip H[n];
    time_snip W[n];
    for (size_t i = 0; i < n; i++)
    {
        cin >> H[i].start >> H[i].end;
    }
    for (size_t i = 0; i < n; i++)
    {
        cin >> W[i].start >> W[i].end;
    }
    double sum = 0;
    auto tem_H = H;
    auto tem_W = W;
    while (true)
    {
        time_snip snip;
        snip.start = max(tem_H->start, tem_W->start);
        snip.end = min(tem_H->end, tem_W->end);
        if (snip.start < snip.end)
        {
            sum += snip.end - snip.start;
        }
        if (tem_H->end < tem_W->end)
        {
            tem_H++;
        }
        else
        {
            tem_W++;
        }
        if (tem_H == H + n || tem_W == W + n)
        {
            break;
        }
    }
    cout << sum << endl;
}

int main()
{
    solve();
    return 0;
}