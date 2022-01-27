#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector> 
using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '['; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << ']'; }
 
void debug_out() { cerr << endl; }
template<typename Head, typename... Tail> void debug_out(Head H, Tail... T) { cerr << ' ' << H; debug_out(T...); }
#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 
#endif

// solution to https://atcoder.jp/contests/dp/tasks/dp_g
struct directed_graph {
    int n;
    vector<vector<int>> adj;

    directed_graph(int _n = -1) {
        if (_n > 0)
            init(_n);
    }

    void init(int _n) {
        n = _n;
        adj.assign(n, vector<int>());
    }

    void add_edge(int a, int b) {
        adj[a].push_back(b);
    }

    int longest_path() {
        vector<int> indeg(n);

        for (auto &e : adj)
            for (int node : e)
                indeg[node]++;

        vector<int> que;

        for (int node = 0; node < n; ++node)
            if (indeg[node] == 0)
                que.push_back(node);

        for (int p = 0; p < int(que.size()); ++p) {
            int node = que[p];

            for (int to : adj[node])
                if (--indeg[to] == 0)
                    que.push_back(to);
        }

        vector<int> dp(n);

        for (int p = int(que.size()); p >= 0; --p) {
            int node = que[p];

            for (int to : adj[node])
                dp[node] = max(dp[node], dp[to] + 1);
        }

        return *max_element(dp.begin(), dp.end());
    }
};

int main() {
    ios::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(0);
#endif

    int N, M;
    cin >> N >> M;
    directed_graph G(N);

    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        G.add_edge(a, b);
    }

    cout << G.longest_path() << '\n';
}