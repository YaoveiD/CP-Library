// source : codeforces neal
// verification : https://atcoder.jp/contests/abc218/submissions/25806818

const int INF = (int) 1e9 + 5;

struct BFS {
    int n;
    vector<vector<int>> adj;
    vector<int> dist;
    vector<int> parent;
 
    BFS(int _n, const vector<vector<int>>& _adj) : adj(_adj) {
        n = _n;
        assert(_n == (int) _adj.size());
    }

    BFS(int _n = 0) {
        init(_n);
    }
 
    void init(int _n) {
        n = _n;
        adj.assign(n, {});
    }
 
    inline void add_directional_edge(int a, int b) {
        adj[a].push_back(b);
    }
 
    inline void add_bidirectional_edge(int a, int b) {
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
 
    void bfs_check(queue<int> &q, int node, int from, int new_dist) {
        if (new_dist < dist[node]) {
            dist[node] = new_dist;
            parent[node] = from;
            q.push(node);
        }
    }
 
    void bfs(const vector<int> &source, int stop = -1) {
        if (n == 0) return;
 
        queue<int> q;
        dist.assign(n, INF);
        parent.assign(n, -1);
 
        for (int src : source)
            bfs_check(q, src, -1, 0);
 
         while (!q.empty()) {
            int top = q.front(); q.pop();
 
            if (top == stop)
                return;

            for (int next_node : adj[top]) {
                bfs_check(q, next_node, top, dist[top] + 1);
            }
        }
    }
};

