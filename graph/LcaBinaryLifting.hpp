// build lca in O(n logn) time and get lca in O(log n) time using binary lifting
struct LCA {
    int n, levels;
    std::vector<std::vector<int>> tree;
    std::vector<int> depth;
    std::vector<std::vector<int>> parent;

    static constexpr int highest_bit(int x) {
        return x == 0 ? -1 : 31 - __builtin_clz(x);
    }

    LCA(const std::vector<std::vector<int>>& _tree = {}) {
        int _n = int(_tree.size());
        if (_n > 0)
            init(_n, _tree);
    }

    void init(int _n, const std::vector<std::vector<int>>& _tree) {
        n = _n;
        levels = highest_bit(n) + 1;
        tree = _tree;
        depth.resize(n);
    }

    void dfs(int v, int p) {
        for (int to : tree[v]) if (to != p) {
            depth[to] = depth[v] + 1;
            parent[to][0] = v;
            dfs(to, v);
        }
    }

    void build(int root = 0) {
        parent.assign(n, std::vector<int>(levels, root));
        dfs(root, -1);

        for (int i = 0; i < n; ++i)
            for (int j = 1; j < levels; ++j)
                parent[i][j] = parent[parent[i][j - 1]][j - 1];
    }

    // make sure to run `build`
    int get_lca(int u, int v) const {
        assert(0 <= u && u < n && 0 <= v && v < n);

        if (depth[u] < depth[v]) std::swap(u, v);

        for (int i = levels - 1; i >= 0; --i)
            if (depth[parent[u][i]] >= depth[v])
                u = parent[u][i];

        if (u == v) return u;

        for (int i = levels - 1; i >= 0; --i)
            if (parent[u][i] != parent[v][i]) {
                u = parent[u][i];
                v = parent[v][i];
            }

        return parent[u][0];
    }

    int get_dist(int u, int v) const {
        int lca = get_lca(u, v);
        return depth[u] + depth[v] - 2 * depth[lca];
    }

    int go_up(int v, int steps) const {
        assert(steps >= 0 && steps < n);

        for (int i = 0; i < levels; ++i)
            if (steps & (1 << i))
                v = parent[v][i];

        return v;
    }
};
