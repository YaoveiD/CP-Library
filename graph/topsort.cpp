
vector<int> toposort(const vector<vector<int>>& adj) {
  int n = int(adj.size());
  vector<int> indeg(n);

  for (int v = 0; v < n; ++v)
    for (int to : adj[v])
      indeg[to]++;

  vector<int> q;

  for (int v = 0; v < n; ++v) if (indeg[v] == 0)
    q.push_back(v);

  for (int ptr = 0; ptr < (int) q.size(); ++ptr) {
    int v = q[ptr];

    for (int to : adj[v])
      if (--indeg[to] == 0)
        q.push_back(to);
  }

  return q;
}