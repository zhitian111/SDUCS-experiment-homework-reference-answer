#include <iostream>
#include <queue>
#include <vector>
using namespace std;

void solve()
{
    int n, k;
    cin >> n >> k;
    long long num[n];
    for (int i = 0; i < n; i++)
    {
        cin >> num[i];
    }
    int left = 0;
    int right = k - 1;
    priority_queue<long long, vector<long long>, greater<long long>> max;
    priority_queue<long long, vector<long long>, less<long long>> min;
    priority_queue<long long, vector<long long>, greater<long long>> to_erase_for_max;
    priority_queue<long long, vector<long long>, less<long long>> to_erase_for_min;
    for (int i = 0; i < k; i++)
    {
        max.push(num[i]);
        min.push(num[i]);
    }
    long long ans1[n - k + 1];
    long long ans2[n - k + 1];
    ans1[0] = max.top();
    ans2[0] = min.top();
    for (int i = 1;i < n - k + 1;i++)
    {
        left++;right++;
        to_erase_for_max.push(num[left - 1]);
        to_erase_for_min.push(num[left - 1]);
        max.push(num[right]);
        min.push(num[right]);
        while (!to_erase_for_max.empty() && !max.empty() && to_erase_for_max.top() == max.top())
        {
            to_erase_for_max.pop();
            max.pop();
        }
        while (!to_erase_for_min.empty() && !min.empty() && to_erase_for_min.top() == min.top())
        {
            to_erase_for_min.pop();
            min.pop();
        }
        ans1[i] = max.top();
        ans2[i] = min.top();
    }
    for (auto i : ans1)
    {
        cout << i << " ";
    }
    cout << endl;
    for (auto i : ans2)
    {
        cout << i << " ";
    }
    cout << endl;
}

int main()
{
    solve();
    return 0;
}