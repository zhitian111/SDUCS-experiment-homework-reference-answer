#include <iostream>
using namespace std;

void solve()
{
  int n, v;
  cin >> n >> v;
  struct item
  {
    int value;
    int weight;
    int group;
  };
  item items[n];
  for (int i = 0; i < n; i++)
  {
    cin >> items[i].value >> items[i].weight >> items[i].group;
  }
}

int main() {}
