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
    vector<T_row> grid;
    vector<vector<int>> dist;
    vector<vector<state>> parent;
 
    grid_bfs(const vector<T_row> &_grid = {}) {
        init(_grid);
    }
 
    void init(const vector<T_row> &_grid = {}) {
        grid = _grid;
        R = int(grid.size());
        C = grid.empty() ? 0 : int(grid[0].size());
    }
 
    bool valid(int r, int c) {
        return 0 <= r && r < R && 0 <= c && c < C;
    }
 
    void bfs_check(queue<state> &q, queue<state> &next_q, const state &s, const state &from_s, int new_dist, int add) {
        assert(add == 0 || add == 1);
 
        if (new_dist < dist[s.row][s.col]) {
            dist[s.row][s.col] = new_dist;
            parent[s.row][s.col] = from_s;
            (add == 0 ? q : next_q).push(s);
        }
    }
    void bfs(const vector<state> &source) {
        if (R == 0 || C == 0) return;
 
        // Two queues are needed for 0-1 BFS.
        queue<state> q, next_q;
        dist.assign(R, vector<int>(C, INF));
        parent.assign(R, vector<state>(C, state()));
 
        for (const state &src : source)
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
 
            swap(q, next_q);
            level++;
        }
    }

    void bfs(const state& src) {
        bfs(vector<state>(1, src));
    }

};
 