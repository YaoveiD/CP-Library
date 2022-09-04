#include <bits/stdc++.h>

struct seg_tree {
    int f(int a, int b) { return a ^ b; }
    int n;
    std::vector<int> s;
    seg_tree(int _n) : n(_n), s(2*_n, 0) {}

    void update(int pos, int val) {
        for (s[pos += n] = val; pos /= 2;)
            s[pos] = f(s[pos*2], s[pos*2+1]);
    }

    int query(int a, int b) {
        int ra = 0, rb = 0;
        for (a += n, b += n; a < b; a /= 2, b /= 2) {
            if (a & 1) ra = f(ra, s[a++]);
            if (b & 1) rb = f(s[--b], rb);
        }
        return f(ra, rb);
    }
};

struct edge_t {
    int node, w;
};

// verification(lca) : Passed https://judge.yosupo.jp/submission/99975
// verification(edge_mode | path query): Passed https://www.luogu.com.cn/problem/P2420, overkill
struct heavy_light {
    // edge_mode: set the edge values to the nodes who are the children of the others.
    static const int vertex_mode = false;
    std::vector<std::vector<edge_t>> adj;
    std::vector<int> top;
    std::vector<int> par;
    std::vector<int> T; // tour start
    std::vector<int> values;
    int n, ts;
    seg_tree tree;

    heavy_light(const std::vector<std::vector<edge_t>> &_adj) : adj(_adj), n(adj.size()), tree(n) {
        par.resize(n);
        top.resize(n);
        T.assign(n, 0);
        values.assign(n, 0);
        ts = 0;
        dfs(0, -1);
        chain_dfs(0, -1);
        build();
    }

    int dfs(int node, int p) {
        int siz = 1;
        int mx = 0;

        for (auto &c : adj[node])
            if (c.node != p) {
                par[c.node] = node;
                int subtree = dfs(c.node, node);
                if (subtree > mx) {
                    mx = subtree;
                    std::swap(adj[node].front(), c);
                }
                siz += subtree;
            }

        return siz;
    }

    void chain_dfs(int node, int p, bool heavy = false) {
        top[node] = heavy ? top[p] : node;
        heavy = true;
        T[node] = ts++;

        for (auto &c : adj[node]) if (c.node != p) {
            chain_dfs(c.node, node, heavy);
            values[c.node] = c.w;
            heavy = false;
        }
    }

    void build() {
        for (int i = 0; i < n; ++i)
            tree.update(T[i], values[i]);
    }

    template<typename T_binary_op>
    // Returns the lca of `u` and `v`.
    int process_path(int u, int v, T_binary_op &&op) {
        while (top[u] != top[v]) {
            // Always pull up the chain with the deeper root.
            if (T[top[u]] > T[top[v]])
                std::swap(u, v);

            int root = top[v];
            op(tree, T[root], T[v] + 1);
            v = par[root];
        }
        if (T[u] > T[v]) std::swap(u, v);
        op(tree, T[u] + (vertex_mode ? 0 : 1), T[v] + 1);
        return u; // u is now an ancestor of v.
    }

    int lca(int u, int v) {
        return process_path(u, v, [&](seg_tree &, int , int) {});
    }

    int query_path(int u, int v) {
        int ans = 0;

        process_path(u, v, [&](seg_tree &tree, int a, int b) {
            ans ^= tree.query(a, b);
        });

        return ans;
    }
};

int main() {
    using namespace std;
    ios::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(nullptr);
#endif

    int N; cin >> N;
    vector<vector<edge_t>> adj(N);

    for (int i = 1; i < N; ++i) {
        int a, b, c; cin >> a >> b >> c;
        a--; b--;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }

    heavy_light HLD(adj);
    int Q; cin >> Q;

    for (int q = 0; q < Q; ++q) {
        int a, b; cin >> a >> b; a--; b--;
        cout << HLD.query_path(a, b) << '\n';
    }
}

