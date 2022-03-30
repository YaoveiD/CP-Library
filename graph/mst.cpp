/*
 *  author: yaoveil
 *  date:   2021-06-22 23:19:00
 */

#include <bits/stdc++.h>
using namespace std;

// source : https://github.com/nealwu/competitive-programming/blob/master/union_find/kruskal.cc
struct union_find {
    // When data[x] < 0, x is a root and -data[x] is its tree size. When data[x] >= 0, data[x] is x's parent.
    vector<int> data;
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
            swap(x, y);

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
    vector<edge> edges;
    vector<bool> original_in_tree;

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
        sort(edges.begin(), edges.end());
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

const int INF = int(1e9) + 442;

template<typename T> struct Prim {
    int n;
    vector<T> d;
    vector<bool> vis;
    vector<vector<T>> g;

    Prim(int _n) {
        n = _n;
        g.assign(n, vector<T>(n, INF));

        for (int i = 0; i < n; ++i)
            g[i][i] = 0;
    }

    void add(int u, int v, int w) {
        g[u][v] = min(g[u][v], w);
    }
  
    int64_t mst(int src = 0) {
        int64_t sum = 0;
        vis.assign(n, false);
        d.assign(n, INF);
        d[src] = 0;

        for (int i = 0; i < n; ++i) {
            int k = -1;

            for (int j = 0; j < n; ++j) {
                if (!vis[j] && (k == -1 || d[j] < d[k])) {
                    k = j;
                }
            }

            if (k == -1)
                return -1; // Graph can't connect

            vis[k] = 1;
            sum += d[k];

            for (int i = 0; i < n; ++i)
                d[i] = min(d[i], g[k][i]);
        }

        return sum;
    }
};