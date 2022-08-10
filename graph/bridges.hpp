#include <bits/stdc++.h>

// Solution to https://leetcode.com/contest/weekly-contest-154/problems/critical-connections-in-a-network/
// source : https://github.com/nealwu/competitive-programming/blob/master/graph_theory/bridges.cc

struct find_bridges {
    struct edge {
        int node, index;

        edge() {}

        edge(int _node, int _index) : node(_node), index(_index) {}
    };

    int n, edges;
    std::vector<std::vector<edge>> adj;
    std::vector<std::array<int, 2>> edge_list;
    std::vector<int> tour_start;
    std::vector<int> low_link;

    std::vector<bool> visited;
    std::vector<bool> is_bridge;
    int tour;

    find_bridges(int _n = 0) {
        init(_n);
    }

    void init(int _n) {
        n = _n;
        edges = 0;
        adj.assign(n, {});
        edge_list.clear();
        tour_start.resize(n);
        low_link.resize(n);
    }

    void add_edge(int a, int b) {
        adj[a].emplace_back(b, edges);
        adj[b].emplace_back(a, edges);
        edge_list.push_back({a, b});
        edges++;
    }

    void dfs(int node, int parent) {
        assert(!visited[node]);
        visited[node] = true;
        tour_start[node] = tour++;
        low_link[node] = tour_start[node];
        int parent_count = 0;

        for (edge &e : adj[node]) {
            // Skip the first edge to the parent, but allow multi-edges.
            if (e.node == parent && parent_count++ == 0)
                continue;

            if (visited[e.node]) {
                // e.node is a candidate for low_link.
                low_link[node] = std::min(low_link[node], tour_start[e.node]);
            } else {
                dfs(e.node, node);
                is_bridge[e.index] = low_link[e.node] > tour_start[node];
                // e.node is part of our subtree.
                low_link[node] = std::min(low_link[node], low_link[e.node]);
            }
        }
    }

    void solve() {
        visited.assign(n, false);
        is_bridge.assign(edges, false);
        tour = 0;

        for (int i = 0; i < n; i++)
            if (!visited[i])
                dfs(i, -1);
    }
};
