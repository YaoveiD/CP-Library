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

int n;
vector<vector<int>> adj;    // adjacency matrix of graph
const int INF = int(1e9) + 4; // weight INF means there is no edge

struct Edge {
  int w = INF, to = -1;
};

void prim() {
  int total_weight = 0;
  vector<bool> selected(n, false);
  vector<Edge> min_e(n);
  min_e[0].w = 0;

  for (int i = 0; i < n; ++i) {
    int v = -1;
    for (int j = 0; j < n; ++j) {
      if (!selected[j] && (v == -1 || min_e[j].w < min_e[v].w))
        v = j;
    }

    if (min_e[v].w == INF) {
      cout << "No MST!" << endl;
      exit(0);
    }

    selected[v] = true;
    total_weight += min_e[v].w;
    if (min_e[v].to != -1)
      cout << v << " " << min_e[v].to << endl;

    for (int to = 0; to < n; ++to) {
      if (adj[v][to] < min_e[to].w)
        min_e[to] = {adj[v][to], v};
    }
  }

  cout << total_weight << endl;
}