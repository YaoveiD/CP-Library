std::vector<int> toposort(const std::vector<std::vector<int>>& adj) {
    int n = int(adj.size());
    std::vector<int> indeg(n);

    for (int v = 0; v < n; ++v)
        for (int to : adj[v])
            indeg[to]++;

    std::vector<int> q;

    for (int v = 0; v < n; ++v) if (indeg[v] == 0)
        q.push_back(v);

    for (int p = 0; p < int(q.size()); ++p) {
        int v = q[p];

        for (int to : adj[v])
            if (--indeg[to] == 0)
                q.push_back(to);
    }

    return q;
}
