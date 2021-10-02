#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
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

// 0 indexed
// make sure T can handle the sum of elements
template<typename T>
struct range_sum {
    int H, W;
    vector<vector<T>> sum;

    range_sum(const vector<vector<T>>& matrix = {}) {
        if (!matrix.empty())
            build(matrix);
    }

    void build(const vector<vector<T>>& matrix) {
        H = int(matrix.size());
        W = matrix.empty() ? 0 : int(matrix[0].size());

        sum.assign(H + 1, vector<T>(W + 1, 0));

        for (int r = 0; r < H; ++r)
            for (int c = 0; c < W; ++c)
                sum[r + 1][c + 1] = matrix[r][c] + sum[r + 1][c] + sum[r][c + 1] - sum[r][c];
    }

    // upper-left, lower-right  closed interval 
    T query(int r1, int c1, int r2, int c2) {
        return sum[r2 + 1][c2 + 1] - sum[r1][c2 + 1] - sum[r2 + 1][c1] + sum[r1][c1];
    }
};

const int _H = 2000;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  vector<vector<int>> grid(_H + 1, vector<int>(_H + 1));
  int N;
  cin >> N;
  for (int i = 0; i < N; ++i) {
    int x, y, w;
    cin >> x >> y >> w;
    grid[x][y] += w;
  }
  int q;
  cin >> q;
  range_sum<int> rs(grid);
  while (q--) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    cout << rs.query(x1, y1, x2, y2) << '\n';
  }
  return 0;
}