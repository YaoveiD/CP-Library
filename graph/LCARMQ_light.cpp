// source : https://codeforces.com/contest/1328/submission/74421058 ksun
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef vector<int> vi;

template<class T>
struct RMQ {
    vector<vector<T>> mat;
    
    RMQ(const vector<T>& V) : mat(1, V) {
        for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
            mat.emplace_back(sz(V) - pw * 2 + 1);
            rep(j,0,sz(mat[k]))
                mat[k][j] = min(mat[k - 1][j], mat[k - 1][j + pw]);
        }
    }

    T query(int a, int b) {
        assert(a < b); // or return inf if a == b
        int dep = 31 - __builtin_clz(b - a);
        return min(mat[dep][a], mat[dep][b - (1 << dep)]);
    }
};
 
struct LCA {
    int T = 0;
    vi time, path, ret;
    vector<int> parent;
    RMQ<int> rmq;
 
    LCA(vector<vi>& C) : time(sz(C)), parent(sz(C)), rmq((dfs(C,0,-1), ret)) {}
    
    void dfs(vector<vi>& C, int v, int par) {
        parent[v] = par;
        time[v] = T++;
        trav(y, C[v]) if (y != par) {
            path.push_back(v), ret.push_back(time[v]);
            dfs(C, y, v);
        }
    }
 
    int lca(int a, int b) {
        if (a == b) return a;
        tie(a, b) = minmax(time[a], time[b]);
        return path[rmq.query(a, b)];
    }
};