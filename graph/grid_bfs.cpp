const int INF = (int) 1e9 + 5;
const int64_t INF64 = (int64_t) 2e18;
 
const int DIRS = 4;
const int DR[DIRS] = {-1,  0, +1,  0};
const int DC[DIRS] = { 0, +1,  0, -1};
 
// const int DIRS = 8;
// const int DR[DIRS] = {-1, -1, -1,  0, +1, +1, +1,  0};
// const int DC[DIRS] = {-1,  0, +1, +1, +1,  0, -1, -1};

struct state {
    int row, col;

    state(int _row = -1, int _col = -1) : row(_row), col(_col) {}
};

template<typename T_row>
class grid_bfs {
public:
    vector<T_row> grid;
    vector<vector<int>> dist;
    int R, C;

    grid_bfs(const vector<T_row>& _grid = {}) : grid(_grid) {
        R = (int) grid.size();
        C = grid.empty() ? 0 : (int) grid[0].size();
    }

    bool valid(int r, int c) {
        bool in_grid = 0 <= r and r < R and 0 <= c and c < C;
        bool unvisited = dist[r][c] == INF;
        return in_grid and unvisited;
    }

    void bfs(const vector<state>& src) {
        if (R == 0 or C == 0)
            return;

        dist.assign(R, vector<int>(C, INF));
        queue<state> Q;
        
        for (const state& s : src) {
            Q.push(s);
            dist[s.row][s.col] = 0;
        }

        while (!Q.empty()) {
            state current = Q.front();
            Q.pop();
            
            int r = current.row;
            int c = current.col;

            for (int dir = 0; dir < DIRS; ++dir) {
                int nr = r + DR[dir];
                int nc = c + DC[dir];

                // Note: valid returns (nr, nc) in grid and unvisited
                if (valid(nr, nc)) {
                    Q.emplace(nr, nc);
                    dist[nr][nc] = dist[r][c] + 1;
                }
            }
        }
    }

    void bfs(const state& src) {
        bfs(vector<state>(1, src));
    }
};
