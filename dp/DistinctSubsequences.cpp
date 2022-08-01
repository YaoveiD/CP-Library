// source : https://github.com/nealwu/competitive-programming/blob/master/dp/distinct_subsequences.cc
// Counts the number of distinct nonempty subsequences in an array.
template<typename T>
mod_int distinct_subsequences(const std::vector<T> &A) {
    int n = int(A.size());
    std::vector<mod_int> dp(n + 1, 0);
    dp[0] = 1;
    std::map<T, int> last;
    // TODO: replace `last` with a hash map or a vector if applicable.

    for (int i = 0; i < n; i++) {
        dp[i + 1] = 2 * dp[i];

        if (last.find(A[i]) != last.end())
            dp[i + 1] -= dp[last[A[i]]];

        last[A[i]] = i;
    }

    // Remove the empty subsequence.
    return dp[n] - 1;
}