// build lca in O(n logn) time and get lca in O(log n) time using binary lifting
struct LCA {
    int n, levels;
    vector<vector<int>> tree;
    vector<int> depth;
    vector<vector<int>> parent;

    static constexpr int highest_bit(int x) {
        return x == 0 ? -1 : 31 - __builtin_clz(x);
    }

    LCA(const vector<vector<int>>& _tree = {}) {
        int _n = int(_tree.size());
        if (_n > 0)
            init(_n, _tree);
    }

    void init(int _n, const vector<vector<int>>& _tree) {
        n = _n;
        levels = highest_bit(n) + 1;
        tree = _tree;
        depth.resize(n);
    }

    void dfs(int v, int p) {
        for (int to : tree[v]) if (to != p) {
            depth[to] = depth[v] + 1;
            parent[0][to] = v;
            dfs(to, v);
        }
    }

    void build(int root = 0) {
        parent.assign(levels, vector<int>(n, root));
        dfs(root, -1);

        for (int i = 1; i < levels; ++i)
            for (int j = 0; j < n; ++j)
                parent[i][j] = parent[i - 1][parent[i - 1][j]];
    }

    // make sure to run `build`
    int get_lca(int u, int v) const {
        assert(0 <= u && u < n && 0 <= v && v < n);

        if (depth[u] < depth[v])
            swap(u, v);

        for (int i = levels - 1; i >= 0; --i)
            if (depth[parent[i][u]] >= depth[v])
                u = parent[i][u];

        if (u == v)
            return u;

        for (int i = levels - 1; i >= 0; --i)
            if (parent[i][u] != parent[i][v]) {
                u = parent[i][u];
                v = parent[i][v];
            }

        return parent[0][u];
    }

    int get_dist(int u, int v) const {
        int lca = get_lca(u, v);
        return depth[u] + depth[v] - 2 * depth[lca];
    }

    int go_up(int v, int step) {
        int bit = 1;

        while (step) {
            if (step & 1)
                v = parent[bit-1][v];

            bit += 1;
            step >>= 1;
        }

        return v;
    }
};
