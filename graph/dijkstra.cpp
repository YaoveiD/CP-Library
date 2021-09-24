/*
*  author: yaoveil
*  date:   2021-06-22 23:15:20
*/
template <typename T>
//make sure dis has been filled with inf
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

template<typename T>
//make sure dis has been filled with inf
void dijkstra(vector<vector<pair<int, T>>>& edge, vector<T>& dis, int start = 0) {
  priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> pq;
  vector<bool> vis(dis.size(), false);
  dis[start] = 0;
  pq.emplace(dis[start], start);
  while (!pq.empty()) {
    int u = pq.top().second;
    pq.pop();
    if (vis[u]) { continue; }
    vis[u] = true;
    for (auto e : edge[u]) {
      int v = e.first;
      if (dis[u] + e.second < dis[v]) {
        dis[v] = dis[u] + e.second;
        pq.emplace(dis[v], v);
      }
    }
  }
}