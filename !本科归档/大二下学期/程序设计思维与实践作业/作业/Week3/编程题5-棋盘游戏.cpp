#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct point
{
    size_t x, y;
};

void select(point points[],size_t cnt,size_t size,bool selected_col[],bool selected_row[],bool selected_points[],size_t from,size_t k,size_t& ans)
{
    if (cnt == k)
    {
        ans++;
        // for (int j = 0;j < size; j++)
        // {
        //     cout << points[j].x << " " << points[j].y << endl;
        // }
        // cout << endl;
        return;
    }
    for (size_t i = from;i < size;i++)
    {
        if (selected_col[points[i].y] || selected_row[points[i].x] || selected_points[i])
        {
            continue;
        }
        selected_points[i] = true;
        selected_col[points[i].y] = true;
        selected_row[points[i].x] = true;
        // cout << "select point" << points[i].x << " " << points[i].y << endl;
        select(points, cnt + 1, size, selected_col, selected_row, selected_points, i + 1, k, ans);
        selected_points[i] = false;
        selected_col[points[i].y] = false;
        selected_row[points[i].x] = false;
    }
}

size_t C(size_t sum, size_t pick)
{
    if (sum == 0 || pick == 0)
    {
        return 0;
    }
    size_t numerator = 1;
    size_t denominator = 1;
    for (size_t i = 1; i <= pick; i++)
    {
        numerator *= sum - i + 1;
        denominator *= i;
    }
    return numerator / denominator;
}
void solve()
{
    size_t n, k;
    while (true)
    {
        cin >> n >> k;
        if (n == -1 && k == -1)
        {
            return;
        }
        size_t sum = 0;
        string s;
        vector<point> points;
        for (size_t i = 0; i < n; i++)
        {
            cin >> s;
            for (size_t j = 0; j < n; j++)
            {
                if (s[j] == '#')
                {
                    points.push_back({i, j});
                }
            }
        }
        bool selected_col[n] = { false };
        bool selected_row[n] = { false };
        bool selected_points[points.size()] = { false };
        select(points.data(), 0, points.size(), selected_col, selected_row, selected_points, 0, k, sum);
        cout << sum << endl;
    }
}

int main()
{
    solve();
    return 0;
}