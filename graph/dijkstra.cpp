template <typename dist_t, typename edge_t>
vector<dist_t> dijkstra(vector<vector<pair<int, edge_t>>>& adj, int src = 0) {
    priority_queue<pair<dist_t, int>, vector<pair<dist_t, int>>, greater<pair<dist_t, int>>> pq;
    vector<bool> vis(adj.size(), false);
    vector<dist_t> dist(adj.size(), INF);
    dist[src] = 0;
    pq.emplace(0, src);

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if (vis[u]) { continue; }
        vis[u] = true;
    
        for (const auto &e : adj[u]) {
            int v = e.first;
            
            if (dist[u] + e.second < dist[v]) {
                dist[v] = dist[u] + e.second;
                pq.emplace(dist[v], v);
            }
        }
    }

    return dist;
}
