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

// verfication : https://leetcode-cn.com/submissions/detail/254471413/
struct base_ring {
    int n;
    vector<int> next;
    vector<vector<int>> circles;
    vector<int> circle_size;
    vector<int> start_max; // longest path need_start with node. Note: including node
    vector<int> end_max; // longest path end with node. Note: not include circle node, but including node itself.

    base_ring(int _n = -1) {
        if (_n != -1)
            init(_n);
    }

    base_ring(vector<int>& _next) : n(_next.size()), next(_next) {}

    void init(int _n) {
        n = _n;
        next.assign(n, -1);
    }

    void add_edge(int a, int b) {
        next[a] = b;
    }

    void process(bool need_start = false, bool need_end = false) {
        vector<int> indeg(n);
        
        for (int node : next)
            if (node != -1)
                indeg[node]++;

        vector<int> que;

        for (int node = 0; node < n; ++node)
            if (indeg[node] == 0)
                que.push_back(node);

        for (int i = 0; i < int(que.size()); ++i) {
            int node = que[i];
            int to = next[node];

            if (to != -1 && --indeg[to] == 0)
                que.push_back(to);
        }

        circle_size.assign(n, 0);

        for (int node = 0; node < n; ++node)
            if (indeg[node] > 0 && circle_size[node] == 0) {
                int s = 1;

                for (int to = next[node]; to != node; to = next[to])
                    s++;

                circles.emplace_back();
                circles.back().push_back(node);

                for (int to = next[node]; to != node; to = next[to])
                    circles.back().push_back(to);

                for (int c : circles.back())
                    circle_size[c] = s;
            }

        if (need_start) {
            start_max.assign(n, 0);

            for (int i = int(que.size()) - 1; i >= 0; --i) {
                int node = que[i];
                int to = next[node];
                start_max[node] += to == -1 ? 1 : start_max[to];
            }
        }

        if (need_end) {
            end_max.assign(n, 1);

            for (int i = 0; i < int(que.size()); ++i) {
                int node = que[i];
                int to = next[node];

                if (to != -1)
                    end_max[to] = end_max[node] + 1;
            }
        }
    }
};

class Solution {
public:
    int maximumInvitations(vector<int>& next) {
        base_ring A(next);
        A.process(false, true);
        int circle = 0, chain = 0;

        for (auto &c : A.circles) {
            circle = max(int(c.size()), circle);

            if (c.size() == 2)
                chain += A.end_max[c.back()] + A.end_max[c.front()];
        }

        return max(circle, chain);
    }
};

int main() {
    ios::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(0);
#endif

    
}