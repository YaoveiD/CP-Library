#include <bits/stdc++.h>

// source : https://github.com/nealwu/competitive-programming/blob/master/union_find/kruskal.cc
struct union_find {
    // When data[x] < 0, x is a root and -data[x] is its tree size. When data[x] >= 0, data[x] is x's parent.
    std::vector<int> data;
    int components = 0;

    union_find(int n = -1) {
        if (n >= 0)
            init(n);
    }

    void init(int n) {
        data.assign(n + 1, -1);
        components = n;
    }

    int find(int x) {
        return data[x] < 0 ? x : data[x] = find(data[x]);
    }

    int get_size(int x) {
        return -data[find(x)];
    }

    bool unite(int x, int y) {
        x = find(x);
        y = find(y);

        if (x == y)
            return false;

        if (-data[x] < -data[y])
            std::swap(x, y);

        data[x] += data[y];
        data[y] = x;
        components--;
        return true;
    }
};

template<typename T_edge>
struct kruskal {
    struct edge {
        int a, b;
        T_edge weight;
        int index = -1;
        bool in_tree = false;

        edge() {}

        edge(int _a, int _b, T_edge _weight, int _index = -1) : a(_a), b(_b), weight(_weight), index(_index) {}

        bool operator<(const edge &other) const {
            return weight < other.weight;
        }
    };

    union_find UF;
    std::vector<edge> edges;
    std::vector<bool> original_in_tree;

    kruskal(int n = -1) {
        if (n >= 0)
            init(n);
    }

    void init(int n) {
        UF.init(n);
        edges = {};
    }

    void add_edge(int a, int b, T_edge weight) {
        edges.emplace_back(a, b, weight, edges.size());
        original_in_tree.push_back(false);
    }

    template<typename T_sum>
    T_sum solve() {
        std::sort(edges.begin(), edges.end());
        T_sum total = 0;

        for (edge &e : edges)
            if (UF.unite(e.a, e.b)) {
                total += e.weight;
                e.in_tree = true;
                original_in_tree[e.index] = true;
            }

        return total;
    }
};

// source : https://chenshouao.github.io/mkdocs/pages/Algorithm/graph/prim.html

const int64_t INF = int64_t(1e18) + 4242;

template<typename T> struct Prim {
    int n;
    std::vector<T> d;
    std::vector<bool> vis;
    std::vector<std::vector<T>> g;
    std::vector<int> parent;

    Prim(int _n) {
        n = _n;
        // Make sure INF won't overflow.
        g.assign(n, std::vector<T>(n, INF));

        for (int i = 0; i < n; ++i)
            g[i][i] = 0;
    }

    void add(int u, int v, int w) {
        g[u][v] = min(g[u][v], w);
    }
  
    T mst(int src = 0) {
        T sum = 0;
        vis.assign(n, false);
        d.assign(n, INF);
        parent.assign(n, -1);
        d[src] = 0;

        for (int i = 0; i < n; ++i) {
            int k = -1;

            for (int j = 0; j < n; ++j)
                if (!vis[j] && (k == -1 || d[j] < d[k]))
                    k = j;

            if (k == -1)
                return -1; // Graph can't connect

            vis[k] = true;
            sum += d[k];

            for (int j = 0; j < n; ++j)
                if (!vis[j] && g[k][j] < d[j]) {
                    d[j] = g[k][j];
                    parent[j] = k;
                }
        }

        return sum;
    }
};
