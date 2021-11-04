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

// solution to https://www.luogu.com.cn/problem/P3870

int main() {
    ios::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(0);
#endif

    int N, M;
    cin >> N >> M;
    const int SQ = sqrt(N);
    vector<int> which(N);
    vector<int> block_opens(SQ + 1);
    vector<int> tag(SQ + 1);
    vector<int> open(N);

    for (int i = 0; i < N; ++i)
        which[i] = i / SQ;

    // [a, b]
    auto update = [&](int a, int b) -> void {
        int cutoff = min(b + 1, (which[a] + 1) * SQ);

        for (int i = a; i < cutoff; ++i) {
            block_opens[which[i]] -= (open[i] ^ tag[which[i]]);
            open[i] ^= 1;
            block_opens[which[i]] += (open[i] ^ tag[which[i]]);    
        }

        for (int i = which[a] + 1; i < which[b]; ++i) {
            tag[i] ^= 1;
            block_opens[i] = SQ - block_opens[i];
        }

        if (which[a] != which[b])
            for (int i = which[b] * SQ; i <= b; ++i) {
                block_opens[which[b]] -= (open[i] ^ tag[which[b]]);
                open[i] ^= 1;
                block_opens[which[i]] += (open[i] ^ tag[which[b]]);
            }
    };

    // [a, b)
    auto query = [&](int a, int b) -> int {
        int ret = 0;
        int cutoff = min(b + 1, (which[a] + 1) * SQ);

        for (int i = a; i < cutoff; ++i)
            ret += (open[i] ^ tag[which[i]]);

        for (int i = which[a] + 1; i < which[b]; ++i)
            ret += block_opens[i];

        if (which[a] != which[b])
            for (int i = which[b] * SQ; i <= b; ++i)
                ret += (open[i] ^ tag[which[i]]);

        return ret;
    };

    while (M--) {
        int type, a, b;
        cin >> type >> a >> b;
        --a; --b;

        if (type == 0) {
            update(a, b);
        } else {
            cout << query(a, b) << '\n';
        }
    }
}