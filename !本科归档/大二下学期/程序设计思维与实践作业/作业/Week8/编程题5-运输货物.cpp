#include <algorithm>
#include <cstddef>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <tuple>
#include <vector>
#include <unordered_map>
using namespace std;

// from to weight time
typedef tuple<size_t, size_t, size_t , size_t> Edge;

auto INF = numeric_limits<size_t>::max();

size_t spfa_with_limit(vector<vector<Edge>>& edges, size_t from, size_t to, size_t min_weight, size_t nodes_cnt, size_t time_limit)
{
  vector<size_t> dist(nodes_cnt + 1, INF);
  dist[from] = 0;
  queue<size_t> q;
  unordered_map<size_t, bool> in_queue;
  q.push(from);
  in_queue[from] = true;
  while (!q.empty())
  {
    auto u = q.front();
    q.pop();
    in_queue[u] = false;
    if (u == to)
    {
      if (dist[u] > time_limit)
      {
        return INF;
      }
      return dist[u];
    }
    for (auto& e : edges[u])
    {
      auto v = get<1>(e);
      auto w = get<2>(e);
      auto t = get<3>(e);
      if (w < min_weight)
      {
        continue;
      }
      if (dist[v] > dist[u] + t && dist[u] + t <= time_limit)
      {
        dist[v] = dist[u] + t;
        if (in_queue[v] == false)
        {
          q.push(v);
          in_queue[v] = true;
        }
      }
    }
  }
  return INF;
}

void solve()
{
  size_t X;
  cin >> X;
  vector<size_t> ans;
  size_t max_weight = 0;
  while (X-- > 0)
  {
    size_t N, M, T;
    cin >> N >> M >> T;
    vector<vector<Edge>> edges(N + 1);
    auto nodes_cnt = N;
    auto time_limit = T;
    vector<size_t> weights;
    for (size_t i = 0; i < M; i++)
    {
      size_t u, v;
      size_t w;
      size_t t;
      cin >> u >> v >> w >> t;
      max_weight = max(max_weight, w);
      weights.push_back(w);
      edges[u].push_back(Edge(u, v, w, t));
      edges[v].push_back(Edge(v, u, w, t));
    }
    auto from = 1;
    auto to = N;
    size_t left = 0;
    auto right = weights.size() - 1;
    sort(weights.begin(), weights.end());
    vector<size_t> ans_tmp;
    while (left <= right)
    {
      auto mid = (left + (right - left) / 2);
      auto dist = spfa_with_limit(edges, from, to, weights[mid], nodes_cnt, time_limit);
      if (dist == INF)
      {
        right = mid - 1;
      }
      else
      {
        ans_tmp.push_back(weights[mid]);
        left = mid + 1;
      }
    }
    ans.push_back(*max_element(ans_tmp.begin(), ans_tmp.end()));
  }
  for (auto a : ans)
  {
    cout << a << endl;
  }
}

int main()
{
  // freopen("input.txt", "r", stdin);
  solve();
  return 0;
}