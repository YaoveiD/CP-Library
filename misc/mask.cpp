// For every mask, computes the sum of `values[sub]` where `sub` is a submask of mask.
template<typename T_out, typename T_in>
std::vector<T_out> submask_sums(int n, const std::vector<T_in> &values) {
    assert(int(values.size()) == 1 << n);
    std::vector<T_out> dp(values.begin(), values.end());

    // Broken profile DP where the intermediate DP state consists of the i-th suffix of the previous row and the i-th
    // prefix of the current row.
    for (int i = 0; i < n; i++)
        for (int base = 0; base < 1 << n; base += 1 << (i + 1))
            for (int mask = base; mask < base + (1 << i); mask++)
                dp[mask + (1 << i)] += dp[mask];

    return dp;
}

// For every mask, computes the sum of `values[sup]` where mask is a submask of `sup`.
template<typename T_out, typename T_in>
std::vector<T_out> supermask_sums(int n, std::vector<T_in> values) {
    reverse(values.begin(), values.end());
    std::vector<T_out> result = submask_sums<T_out>(n, values);
    reverse(result.begin(), result.end());
    return result;
}

// submask is submasks of mask in [0, mask) from small to big
// s is submasks of mask from in (0, mask] from big to small
void submasks(int mask) {
    for (int s = mask; s != 0; s = (s - 1) & mask) {
        int submask = mask ^ s;
    }
}

// suppermask of mask in [mask, 1 << n) from small to big
void superrmasks(int mask, int n) {
    for (int s = mask; s < 1 << n; s = (s + 1) | mask) {
    }
}

// flip i-th bit
inline int flip(int mask, int k) {
    return mask ^ (1 << k);
}

// set k-th bit
inline int set(int mask, int k) {
    return mask | (1 << k);
}

// reset k-th bit
inline int reset(int mask, int k) {
    return mask & (~(1 << k));
}

// minus the lowest bit `1` from mask
inline int reset_last(int mask) {
    return mask & (mask - 1);
}

// lowest bit `1` of mask
inline int lowbit(int mask) {
    return mask & -mask;
}

// returns true if mask has consective bit `1`
inline bool has_adj(int mask) {
    return mask << 1 & mask;
}

int main() {
    submasks(22);
    superrmasks(22, 5);
}
