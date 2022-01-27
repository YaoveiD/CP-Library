/*
*  author: yaoveil
*  date:   2021-06-22 23:15:20
*/

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