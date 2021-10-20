#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <vector>
 
using namespace std;

// build lca in O(n logn) time and get lca in O(log n) time using binary lifting
struct LCA {
    int n, levels;
    vector<vector<int>> tree;
    vector<int> depth;
    vector<vector<int>> parent;

    static constexpr int highest_bit(int x) {
        return x == 0 ? -1 : 31 - __builtin_clz(x);
    }

    LCA(const vector<vector<int>> _tree = {}) {
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
        return depth[u] + depth[v] - depth[lca];
    }
};

template<typename T, typename T_iterable>
map<T, int> compress(const T_iterable& seq, int start = 1) {
    set<T> values;
    for (const auto& item : seq) {
        values.insert(item);
    }

    map<T, int> comp;
    for (const auto& value : values)
        comp[value] = start++;

    return comp;
}

int main() {
    ios::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(0);
#endif

    int N;
    cin >> N;
    int root = -1;
    vector<vector<int>> tree(N);
    set<int> values;
    vector<pair<int, int>> E(N);

    for (int i = 0; i < N; ++i) {
        int u, v;
        cin >> u >> v;
        E[i] = {u, v};
        values.insert(u);
        if (v == -1) {
            root = u;
            continue;
        }
        values.insert(v);
    }

    auto comp = compress<int>(values, 0);
    root = comp[root];

    for (const auto& e : E) if (e.second != -1) {
        int u = comp[e.first];
        int v = comp[e.second];
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    LCA lca(tree);
    lca.build(root);

    int M;
    cin >> M;

    while (M--) {
        int u, v;
        cin >> u >> v;
        u = comp[u]; v = comp[v];
        int a = lca.get_lca(u, v);

        if (a == u) {
            cout << 1 << '\n';
        } else if (a == v) {
            cout << 2 << '\n';
        } else {
            cout << 0 << '\n';
        }
    }
}