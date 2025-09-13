#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <typename T> inline T lowbit(const T& x) { return x & -x; }

template <typename T> class TreeArray
{
private:
    size_t cnt;
    vector<T> tree;

public:
    TreeArray(const long long& n) : cnt(n) { tree.assign(2 * n, T()); }
    TreeArray(const TreeArray<T>& rhs) : cnt(rhs.cnt), tree(rhs.tree) {}
    TreeArray(const vector<T>& rhs) : cnt(rhs.size())
    {
        tree.assign(2 * cnt, T());
        for (size_t i = 0; i < cnt; i++)
        {
            tree[i + cnt] = rhs[i];
        }
    }

    void add(const long long& p, const T& val)
    {
        for (long long i = p; i <= cnt; i += lowbit(i))
        {
            tree[i] += val;
        }
    }
    T query(const long long& p) const
    {
        T res = T();
        for (long long i = p; i > 0; i -= lowbit(i))
        {
            res += tree[i];
        }
        return res;
    }
    T query(const long long& l, const long long& r) const
    {
        return query(r) - query(l - 1);
    }
    
    void display()
    {
        for (size_t i = 0; i < cnt;i++)
        {
            cout << tree[i] << " ";
        }
        cout << endl;
    }
};

struct Node
{
    int time;
    int mem;
    bool operator<(const Node& rhs) const
    {
        if (time == rhs.time)
        {            
            return mem < rhs.mem;
        }
        return time < rhs.time;
    }
};

void solve()
{
    size_t n;
    cin >> n;
    Node nodes[n];
    for (size_t i = 0; i < n; i++)
    {
        cin >> nodes[i].time >> nodes[i].mem;
    }
    sort(nodes, nodes + n);
    TreeArray<int> tree(1e6 + 10);
    vector<int> ans(n + 10, 0);
    for (auto i : nodes)
    {
        auto mark = tree.query(i.mem + 1);
        tree.add(i.mem + 1, 1);
        ans[mark]++;
    }
    for (size_t i = 0; i < n; i++)
    {
        cout << ans[i] << "\n";
    }
    
    cout << endl;
}

int main()
{
    // test();
    solve();
    return 0;
}