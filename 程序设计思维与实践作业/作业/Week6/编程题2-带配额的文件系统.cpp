#include <bits/stdc++.h>
#include <cstddef>
using namespace std;

size_t MAX_SIZE = ~(size_t)0;

vector<string> split(const string& s, char delimiter)
{
  vector<string> tokens;
  string token;
  for (char c : s)
  {
    if (c == delimiter)
    {
      tokens.push_back(token);
      token.clear();
    }
    else
    {
      token += c;
    }
  }
  if (!token.empty())
  {
    tokens.push_back(token);
  }
  return tokens;
}

void solve()
{

  int n;
  cin >> n;
  for (int i = 0; i < n; i++)
  {
    char op;
    cin >> op;
    if (op == 'C')
    {
      string path;
      size_t size;
      cin >> path >> size;
      if (true)
      {
        cout << "Y" << endl;
      }
      else
      {
        cout << "N" << endl;
      }
    }
    if (op == 'R')
    {
      string path;
      cin >> path;

      cout << "Y" << endl;
    }
    if (op == 'Q')
    {
      string path;
      cin >> path;
      size_t LD, LR;
      cin >> LD >> LR;
      LD = LD == 0 ? MAX_SIZE : LD;
      LR = LR == 0 ? MAX_SIZE : LR;
      if (true)
      {
        cout << "Y" << endl;
      }
      else
      {
        cout << "N" << endl;
      }
    }
    // tree_all(&root);
  }
}

void test()
{
  string s = "/root/a/b/c/d";
  for (auto&& i : split(s, '/'))
  {
    cout << i << endl;
  }
}

int main()
{
  // solve();
  test();
  return 0;
}
