#define sz(c) int(c.size())

// source : https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/LCA.h
template<typename T>
struct RMQ {
	std::vector<std::vector<T>> mat;
    
    RMQ(const std::vector<T>& V) : mat(1, V) {
        for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
            mat.emplace_back(sz(V) - pw * 2 + 1);
            for (int j = 0; j < sz(mat[k]); ++j)
                mat[k][j] = min(mat[k - 1][j], mat[k - 1][j + pw]);
        }
    }

    T query(int a, int b) const {
        assert(a < b); // or return inf if a == b
        int dep = 31 - __builtin_clz(b - a);
        return min(mat[dep][a], mat[dep][b - (1 << dep)]);
    }
};
 
struct LCA {
    int T = 0;
	std::vector<int> time, path, ret;
	std::vector<int> parent, depth;
    RMQ<int> rmq;
 
    LCA(std::vector<std::vector<int>>& C)
        : time(sz(C)), parent(sz(C)), depth(sz(C)), rmq((dfs(C,0,-1), ret)) {}
    
    void dfs(std::vector<std::vector<int>>& C, int v, int par) {
        parent[v] = par;
        time[v] = T++;
        for (auto y : C[v]) if (y != par) {
            path.push_back(v), ret.push_back(time[v]);
            depth[y] = depth[v] + 1;
            dfs(C, y, v);
        }
    }
 
    int get_lca(int a, int b) const {
        if (a == b) return a;
		std::tie(a, b) = std::minmax(time[a], time[b]);
        return path[rmq.query(a, b)];
    }

    int get_dist(int a, int b) const {
        return depth[a] + depth[b] - 2 * depth[get_lca(a, b)];
    }
};
