/*
*  author: yaoveil
*  date:   2021-06-22 23:15:20
*/
template <typename T>
//make sure dist has been filled with inf
void dijkstra(const graph<T> &g, vector<T>& dist, int start = 0) {
  assert(0 <= start && start < g.n);
  priority_queue<pair<T, int>, vector<pair<T, int> >, greater<pair<T, int> > > s;
  dist[start] = 0;
  s.emplace(dist[start], start);
  while (!s.empty()) {
    T expected = s.top().first;
    int i = s.top().second;
    s.pop();
    if (dist[i] != expected) {
      continue;
    }
    for (int id : g.g[i]) {
      auto &e = g.edges[id];
      int to = e.from ^ e.to ^ i;
      if (dist[i] + e.cost < dist[to]) {
        dist[to] = dist[i] + e.cost;
        s.emplace(dist[to], to);
      }
    }
  }
  // returns inf if there's no path
}

template<typename edge_t, typename dist_t>
void dijkstra(vector<vector<pair<int, edge_t>>>& edge, vector<dist_t>& dist, int start = 0) {
  priority_queue<pair<dist_t, int>, vector<pair<dist_t, int>>, greater<pair<dist_t, int>>> pq;
  vector<bool> vis(dist.size(), false);
  dist.assign(edge.size(), INF);
  dist[start] = 0;
  pq.emplace(dist[start], start);

  while (!pq.empty()) {
    int u = pq.top().second;
    pq.pop();
    if (vis[u]) { continue; }
    vis[u] = true;
  
    for (const auto &e : edge[u]) {
      int v = e.first;
      if (dist[u] + e.second < dist[v]) {
        dist[v] = dist[u] + e.second;
        pq.emplace(dist[v], v);
      }
    }
  }
}