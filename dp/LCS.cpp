
template<typename T_array>
int LCS(const T_array& S, const T_array& T) {
    int N = int(S.size()), M = int(T.size());
    vector<vector<int>> dp(N + 1, vector<int>(M + 1));

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            if (S[i] == T[j]) {
                dp[i + 1][j + 1] = dp[i][j] + 1;
            } else {
                dp[i + 1][j + 1] = max(dp[i + 1][j], dp[i][j + 1]);
            }

    return dp[N][M];
}

template<typename T_array>
string LCS(const T_array& S, const T_array& T) {
    int N = int(S.size()), M = int(T.size());
    vector<vector<int>> dp(N + 1, vector<int>(M + 1));
    vector<vector<bool>> previous(N + 1, vector<bool>(M + 1));

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            if (S[i] == T[j]) {
                dp[i + 1][j + 1] = dp[i][j] + 1;                
            } else {
                dp[i + 1][j + 1] = max(dp[i + 1][j], dp[i][j + 1]);
                previous[i + 1][j + 1] = dp[i + 1][j] == dp[i + 1][j + 1];
            }

    int i = N, j = M;
    string common;

    while (i > 0 && j > 0) {
        if (S[i - 1] == T[j - 1]) {
            common += S[i - 1];
            i--; j--;
            continue;
        }

        if (previous[i][j])
            j--;
        else
            i--;
    }

    reverse(common.begin(), common.end());
    return string;
}