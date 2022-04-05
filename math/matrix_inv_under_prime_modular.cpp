const int MOD = int(1e9) + 7;
const int64_t MODSQ = int64_t(MOD) * MOD;

int64_t modpow(int64_t a, int64_t b) {
  assert(b >= 0);

  int64_t result = 1;
  
  while (b) {
    if (b & 1) {
      result = result * a % MOD;
    }
    a = a * a % MOD;
    b >>= 1;
  }
  
  return result;
}

inline int64_t inverse(int64_t a) {
    return modpow(a, MOD - 2);
}

template<typename value_t>
using matrix = vector<vector<value_t>>;

// solution to https://www.luogu.com.cn/problem/P4783
// returns the inverse matrix of matrix A under prime modular using guass jordan,
// Note: if there's no sulotion, returns an empty matrix.

template<typename T>
matrix<T> inv(const matrix<T>& A) {
    assert(A.size() == A[0].size());
    int N = int(A.size());
    matrix<T> M(N, vector<T>(N * 2));

    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c)
            M[r][c] = A[r][c];

        M[r][r + N] = 1;
    }

    for (int i = 0; i < N; ++i) {
        int max_row = i;

        for (int j = i + 1; j < N; ++j)
            if (A[j][i] > A[max_row][i])
                max_row = j;

        if (max_row != i)
            for (int c = i; c < N + N; ++c)
                swap(M[max_row][c], M[i][c]);

        if (M[i][i] == 0)
            return matrix<T>();

        int64_t inv_ = inverse(M[i][i]);

        for (int r = 0; r < N; ++r)
            if (r != i && M[r][i]) {
                int64_t t = M[r][i] * inv_ % MOD;
                
                for (int c = i; c < N + N; ++c)
                    M[r][c] = (MODSQ + M[r][c] - M[i][c] * t) % MOD;
            }

        for (int c = 0; c < N + N; ++c)
            M[i][c] = M[i][c] * inv_ % MOD;
    }

    matrix<T> ans(N, vector<T>(N));

    for (int r = 0; r < N; ++r)
        for (int c = 0; c < N; ++c)
            ans[r][c] = M[r][c + N];

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(0);
#endif

    int N;
    cin >> N;
    matrix<int64_t> A(N, vector<int64_t>(N));

    for (auto& row : A)
        for (auto& a : row)
            cin >> a;

    auto inv_A = inv(A);

    if (inv_A.empty()) {
        cout << "No Solution" << '\n';
    } else {
        for (int r = 0; r < N; ++r)
            for (int c = 0; c < N; ++c)
                cout << inv_A[r][c] << (c < N - 1 ? ' ' : '\n');
    }
}