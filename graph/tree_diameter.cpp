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

// DP with DFS O(n) time get the diameter of a tree
struct dfs_tree_diameter {
    int n, d;
    vector<vector<int>> tree;
    vector<int> D;

    dfs_tree_diameter(const vector<vector<int>>& _tree) : tree(_tree) {
        n = int(_tree.size());
        D.resize(n);
        d = 0;
    }

    void dfs(int v, int p) {
        for (int to : tree[v]) if (to != p) {
            dfs(to, v);
            d = max(d, D[v] + D[to] + 1);
            D[v] = max(D[v], D[to] + 1);
        }
    }

    int get_diameter() {
        dfs(0, -1);
        return d;
    }
};

// do BFS twice to get the diameter of a tree in O(n) time
struct bfs_tree_diameter {
    int n;
    vector<vector<int>> tree;
    vector<int> D;

    bfs_tree_diameter(const vector<vector<int>>& _tree) : tree(_tree) {
        n = int(_tree.size());
    }

    int bfs(int src) {
        D.assign(n, -1);
        queue<int> q;
        q.push(src);
        D[src] = 0;

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            for (int to : tree[v]) if (D[to] == -1) {
                D[to] = D[v] + 1;
                q.push(to);
            }
        }

        return int(max_element(D.begin(), D.end()) - D.begin());
    }

    int get_diameter() {
        int u = bfs(0);
        int v = bfs(u);
        return D[v];
    }
};

int main() {
    ios::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(0);
#endif

    int N;
    cin >> N;
    vector<vector<int>> tree(N);

    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    bfs_tree_diameter td(tree);
    cout << 3 * td.get_diameter() << '\n';
}