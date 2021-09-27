
template<typename iterable_T>
int LCS(const iterable_T& S, const iterable_T& T) {
    int N = (int) S.size();
    int M = (int) T.size();

    vector<vector<int>> dp(N + 1, vector<int>(M + 1));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (S[i] == T[j]) {
                dp[i + 1][j + 1] = dp[i][j] + 1;
            } else {
                dp[i + 1][j + 1] = max(dp[i + 1][j], dp[i][j + 1]);
            }
        }
    }

    return dp[N][M];
}
