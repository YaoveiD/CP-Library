template <typename edge_t, typename dist_t>
struct SPFA {
    int n;
    std::vector<std::vector<std::pair<int, edge_t>>> adj;
    std::vector<int> times;
    std::vector<bool> inque;
    std::vector<dist_t> dist;

    SPFA(int _n = -1) {
        if (_n > 0)
            init(_n);
    }

    SPFA(const std::vector<std::vector<std::pair<int, edge_t>>> &_adj)
        : n(int(_adj.size())), adj(_adj) {}

    void init(int _n) {
        n = _n;
        adj.assign(n, std::vector<std::pair<int, edge_t>>());
    }

    void init(const std::vector<std::vector<std::pair<int, edge_t>>> &_adj) {
        n = int(_adj.size());
        adj = _adj;
    }

    void add_edge(int a, int b, edge_t c) {
        adj[a].emplace_back(b, c);
    }

    // Returns `true` if negtive circle detected.
    bool solve(int src) {
        static const dist_t INF = std::numeric_limits<dist_t>::max() / 2; // Note: dummy
        dist.assign(n, INF);
        times.assign(n, 0);
        inque.assign(n, false);
        std::queue<int> q;
        dist[src] = 0;
        times[src] = 1;
        q.push(src);

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            inque[node] = false;

            for (auto &e : adj[node]) {
                int to = e.first;

                if (dist[to] > dist[node] + e.second) {
                    dist[to] = dist[node] + e.second;

                    if (!inque[to]) {
                        if (++times[to] > n)
                            return true;

                        q.push(to);
                        inque[to] = true;
                    }
                }
            }
        }

        return false;
    }
};
