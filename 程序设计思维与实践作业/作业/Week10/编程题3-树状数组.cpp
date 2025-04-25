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
};

void solve()
{
  long long n, q;
  cin >> n >> q;
  TreeArray<long long> t(n);
  for (long long i = 1; i <= n; i++)
  {
    long long x;
    cin >> x;
    t.add(i, x);
  }
  for (long long i = 0; i < q; i++)
  {
    long long o;
    cin >> o;
    if (o == 1)
    {
      long long i, x;
      cin >> i >> x;
      t.add(i, x);
    }
    if (o == 2)
    {
      long long l, r;
      cin >> l >> r;
      cout << t.query(l, r) << endl;
    }
  }
}

int main()
{
  solve();
  return 0;
}
