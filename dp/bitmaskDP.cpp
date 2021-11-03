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

// solution to https://www.luogu.com.cn/problem/P1896

int64_t dp[9][512][82];

inline int pct(int x) {
    return __builtin_popcount(x);
}

int main() {
    ios::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(0);
#endif

    int N, K;
    cin >> N >> K;
    vector<int> row;
    row.reserve(1 << N);

    for (int mask = 0; mask < 1 << N; ++mask)
        if (!(mask << 1 & mask)) {
            row.push_back(mask);
        }

    for (int mask : row) if (pct(mask) <= K)
        dp[0][mask][pct(mask)] = 1;

    for (int r = 1; r < N; ++r)
        for (int mask : row)
            for (int pre_mask : row) {
                if (pre_mask & mask)
                    continue;
                if (mask << 1 & pre_mask)
                    continue;
                if (pre_mask << 1 & mask)
                    continue;

                for (int k = pct(mask); k <= K; ++k)
                    dp[r][mask][k] += dp[r - 1][pre_mask][k - pct(mask)];
            }

    int64_t total = 0;

    for (int mask : row)
        total += dp[N - 1][mask][K];

    cout << total << '\n';
}