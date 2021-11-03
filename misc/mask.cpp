#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
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

// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
template<class Fun> class y_combinator_result {
    Fun fun_;
public:
    template<class T> explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
    template<class ...Args> decltype(auto) operator()(Args &&...args) { return fun_(std::ref(*this), std::forward<Args>(args)...); }
};
template<class Fun> decltype(auto) y_combinator(Fun &&fun) { return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun)); }

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '['; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << ']'; }
 
void debug_out() { cerr << endl; }
template<typename Head, typename... Tail> void debug_out(Head H, Tail... T) { cerr << ' ' << H; debug_out(T...); }
#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 
#endif

// For every mask, computes the sum of `values[sub]` where `sub` is a submask of mask.
template<typename T_out, typename T_in>
vector<T_out> submask_sums(int n, const vector<T_in> &values) {
    assert(int(values.size()) == 1 << n);
    vector<T_out> dp(values.begin(), values.end());

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
vector<T_out> supermask_sums(int n, vector<T_in> values) {
    reverse(values.begin(), values.end());
    vector<T_out> result = submask_sums<T_out>(n, values);
    reverse(result.begin(), result.end());
    return result;
}

// submask is submasks of mask in [0, mask) from small to big
// s is submasks of mask from in (0, mask] from big to small
void submasks(int mask) {
    for (int s = mask; s != 0; s = (s - 1) & mask) {
        int submask = mask ^ s;
        debug(submask, s);
    }
}

// suppermask of mask in [mask, 1 << n) from small to big
void superrmasks(int mask, int n) {
    for (int s = mask; s < 1 << n; s = (s + 1) | mask) {
        debug(s);
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