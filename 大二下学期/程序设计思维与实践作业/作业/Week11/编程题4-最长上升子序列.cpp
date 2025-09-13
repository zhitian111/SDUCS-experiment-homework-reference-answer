#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

template <typename T> inline T lowbit(const T& x) { return x & -x; }

template <typename T> class TreeArray
{
private:
  size_t cnt;
  vector<T> tree;

public:
  TreeArray(const long long& n) : cnt(n) { tree.assign(2 * n, T()); }
  TreeArray(const long long& n, const T& val) : cnt(n)
  {
    tree.assign(2 * n, val);
  }
  
  void add(const long long& p, const T& val)
  {
    for (long long i = p; i <= cnt; i += lowbit(i))
    {
      tree[i] = max(tree[i], val);
    }
  }
  T query(const long long& p) const
  {
    T res = T();
    for (long long i = p; i > 0; i -= lowbit(i))
    {
      res = max(res, tree[i]);
    }
    return res;
  }
  void display()
  {
    for (size_t i = 0; i< cnt;i++)
    {
      cout << tree[i] << " ";
    }
    cout << endl;
  }
  void modify(const long long& p, const T& val)
  {
    add(p, val);
  }
};



// 树状数组优化的LIS算法
void solve()
{
  size_t n;
  cin >> n;
  vector<size_t> a(n + 1);
  a[0] = 0;
  size_t tree_size = 0;
  for (size_t i = 1; i <= n; i++)
  {
    cin >> a[i];
    tree_size = max(tree_size, a[i]);
  }
  
  // 树状数组的第i项用于维护以i为结尾的上升子序列的最长长度
  TreeArray<size_t> ta(tree_size + 1);
  for (size_t i = 1; i <= n; i++)
  {
    auto tem = ta.query(a[i] - 1);
    ta.modify(a[i],tem + 1);
  }
  cout << ta.query(tree_size) << endl;
}

int main()
{
  solve();
  return 0;
}
