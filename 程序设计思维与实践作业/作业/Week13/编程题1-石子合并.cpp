#include <bits/stdc++.h>
using namespace std;

void solve() {
    int N;
    cin >> N;
    vector<int> stone(N);
    for (int i = 0; i < N; ++i)
    {
        cin >> stone[i];
    }

    vector<int> stones(2 * N);
    for (int i = 0; i < 2 * N; ++i)
    {
        stones[i] = stone[i % N];
    }

    vector<int> s(2 * N + 1, 0);
    for (int i = 1; i <= 2 * N; ++i)
    {
        s[i] = s[i - 1] + stones[i - 1];
    }

    const int INF = 1e9;
    vector<vector<int>> dp_min(2 * N, vector<int>(2 * N, INF));
    vector<vector<int>> dp_max(2 * N, vector<int>(2 * N, -INF));

    for (int i = 0; i < 2 * N; ++i)
    {
        dp_min[i][i] = 0;
        dp_max[i][i] = 0;
    }

    for (int len = 2; len <= N; ++len)
    {
        for (int i = 0; i + len - 1 < 2 * N; ++i)
        {
            int j = i + len - 1;
            for (int k = i; k < j; ++k)
            {
                int sum = s[j + 1] - s[i];
                dp_min[i][j] = min(dp_min[i][j], dp_min[i][k] + dp_min[k + 1][j] + sum);
                dp_max[i][j] = max(dp_max[i][j], dp_max[i][k] + dp_max[k + 1][j] + sum);
            }
        }
    }

    int min_total = INF;
    int max_total = -INF;
    for (int i = 0; i < N; ++i)
    {
        int j = i + N - 1;
        if (dp_min[i][j] < min_total)
        {
            min_total = dp_min[i][j];
        }
        if (dp_max[i][j] > max_total)
        {
            max_total = dp_max[i][j];
        }
    }

    cout << min_total << endl;
    cout << max_total << endl;
}

int main()
{
    solve();
    return 0;
}