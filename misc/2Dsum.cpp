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

    // upper-left, lower-right -> closed, open   
    inline T query(int r1, int c1, int r2, int c2) {
        return sum[r2][c2] - sum[r1][c2] - sum[r2][c1] + sum[r1][c1];
    }
};