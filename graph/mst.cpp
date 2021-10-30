/*
 *  author: yaoveil
 *  date:   2021-06-22 23:19:00
 */

#include <bits/stdc++.h>
using namespace std;

// source : github the-tourist algos
template <typename T> vector<int> kruskal(const undigraph<T> &g, T &ans) {
  vector<int> order(g.edges.size());
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(),
       [&g](int a, int b) { return g.edges[a].cost < g.edges[b].cost; });
  dsu d(g.n);
  vector<int> ans_list;
  ans = 0;
  for (int id : order) {
    auto &e = g.edges[id];
    if (d.get(e.from) != d.get(e.to)) {
      d.unite(e.from, e.to);
      ans_list.push_back(id);
      ans += e.cost;
    }
  }
  return ans_list;
  // returns edge ids of minimum "spanning" forest
}

// prim. I don't know, havn't been verified
// source : https://chenshouao.github.io/mkdocs/pages/Algorithm/graph/prim.html

const int INF = int(1e9) + 442;

template<typename T> struct Prim {
  int n;
  vector<T> d;
  vector<bool> vis;
  vector<vector<T>> g;

  Prim(int _n) {
    n = _n;
    g.assign(n, vector<T>(n, INF));

    for (int i = 0; i < n; ++i)
      g[i][i] = 0;
  }

  void add(int u, int v, int w) {
    g[u][v] = min(g[u][v], w);
  }
  
  int64_t mst(int src = 0) {
    int64_t sum = 0;
    vis.assign(n, false);
    d.assign(n, INF);
    d[src] = 0;

    for (int i = 0; i < n; ++i) {
      int k = -1;

      for (int j = 0; j < n; ++j) {
        if (!vis[j] && (k == 0 || d[j] < d[k])) {
          k = j;
        }
      }

      if (k == -1)
        return -1; // Graph cant connect

      vis[k] = 1;
      sum += d[k];

      for (int i = 0; i < n; ++i)
        d[i] = min(d[i], g[k][i]);
    }

    return sum;
  }
};