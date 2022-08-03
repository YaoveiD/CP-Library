//https://codeforces.com/contest/1520/submission/115246387

const int INF = int(1e9) + 5;
 
const int DIRS = 4;
const int DR[DIRS] = {-1,  0, +1,  0};
const int DC[DIRS] = { 0, +1,  0, -1};
 
// const int DIRS = 8;
// const int DR[DIRS] = {-1, -1, -1,  0, +1, +1, +1,  0};
// const int DC[DIRS] = {-1,  0, +1, +1, +1,  0, -1, -1};
 
struct state {
    int row = -1, col = -1;
 
    state() {}
 
    state(int _row, int _col) : row(_row), col(_col) {}
};
 
template<typename T_row>
struct grid_bfs {
    int R, C;
	std::vector<T_row> grid;
	std::vector<std::vector<int>> dist;
	std::vector<std::vector<state>> parent;
 
    grid_bfs(const std::vector<T_row> &_grid = {}) {
        init(_grid);
    }
 
    void init(const std::vector<T_row> &_grid = {}) {
        grid = _grid;
        R = int(grid.size());
        C = grid.empty() ? 0 : int(grid[0].size());
    }
 
    bool valid(int r, int c) {
        return 0 <= r && r < R && 0 <= c && c < C;
    }
 
    void bfs_check(std::queue<state> &q, std::queue<state> &next_q, const state &s, const state &from_s, int new_dist, int add) {
        assert(add == 0 || add == 1);
 
        if (new_dist < dist[s.row][s.col]) {
            dist[s.row][s.col] = new_dist;
            parent[s.row][s.col] = from_s;
            (add == 0 ? q : next_q).push(s);
        }
    }
    
    void bfs(const std::vector<state> &sources) {
        if (R == 0 || C == 0) return;
 
        // Two queues are needed for 0-1 BFS.
		std::queue<state> q, next_q;
        dist.assign(R, std::vector<int>(C, INF));
        parent.assign(R, std::vector<state>(C, state()));
 
        for (const state &src : sources)
            bfs_check(q, next_q, src, state(), 0, 0);
 
        int level = 0;
 
        while (!q.empty() || !next_q.empty()) {
            while (!q.empty()) {
                state top = q.front(); q.pop();
                int r = top.row, c = top.col;
 
                if (level > dist[r][c])
                    continue;
                
                for (int dir = 0; dir < DIRS; dir++) {
                    int nr = r + DR[dir];
                    int nc = c + DC[dir];
 
                    if (valid(nr, nc) && grid[nr][nc] >= 0) {
                        int add = 1;
                        bfs_check(q, next_q, state(nr, nc), top, dist[r][c] + add, add);
                    }
                }
            }
 
			std::swap(q, next_q);
            level++;
        }
    }

    void bfs(const state& src) {
        bfs(std::vector<state>(1, src));
    }
};
 
