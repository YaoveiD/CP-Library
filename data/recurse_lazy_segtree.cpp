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

struct segment_change {
    int64_t to_add;

    segment_change(int64_t _add = 0) : to_add(_add) {}

    void combine(const segment_change& other) {
        to_add += other.to_add;
    }
};

const int64_t INF = int64_t(1e18);

struct segment {
    int64_t minima;

    segment(int64_t _minima = 0) : minima(_minima) {}

    void apply(const segment_change& change) {
        minima += change.to_add;
    }
};

const segment identity(INF);

// solution to https://codeforces.com/edu/course/2/lesson/5/2/practice/contest/279653/problem/A
// this can handle the following two operations
// 1. add v to segment from a to b O(logn)
// 2. find the minimum on segment fomr a to b O(logn)

struct seg_tree {
    int n;
    vector<segment> tree;
    vector<segment_change> changes;

    // full 
    void init(int _n) {
        n = 1;
        while (n < _n) n *= 2;
        tree.assign(n * 2, segment());
        changes.assign(n * 2, segment_change());
    }

    // combine two segments
    segment join(const segment& a, const segment& b) {
        return a.minima < b.minima ? a : b; // TODO
    }

    // apply the change on segment and combine the changes
    void apply_and_combine(int p, const segment_change& change) {
        tree[p].apply(change);

        if (p < n)
            changes[p].combine(change);
    }

    // push up left and right segments
    void pull(int p) {
        tree[p] = join(tree[p * 2], tree[p * 2 + 1]);
    }

    // push down the segment change
    void push(int p, int L, int R) {
        if (changes[p].to_add != 0) {
            apply_and_combine(p * 2, changes[p]);
            apply_and_combine(p * 2 + 1, changes[p]);
            changes[p] = segment_change();
        }
    }

    void update(int p, int L, int R, int a, int b, const segment_change& change) {
        if (a <= L && R <= b) {
            apply_and_combine(p, change); // Note : don't use apply
            return;
        }

        if (b < L || a > R)
            return;

        push(p, L, R);
        int mid = (L + R) / 2;
        update(p * 2, L, mid, a, b, change);
        update(p * 2 + 1, mid + 1, R, a, b, change);
        pull(p);
    }

    // Note: [a, b]
    void update(int a, int b, int add) {
        update(1, 0, n - 1, a, b, segment_change(add));
    }

    segment query(int p, int L, int R, int a, int b) {
        if (a <= L && R <= b) {
            return tree[p];
        }

        if (b < L || a > R)
            return identity;

        push(p, L, R);
        int mid = (L + R) / 2;
        return join(query(p * 2, L, mid, a, b), query(p * 2 + 1, mid + 1, R, a, b));
    }

    // Note: [a, b]
    int64_t query(int a, int b) {
        return query(1, 0, n - 1, a, b).minima;
    }
};

int main() {
    ios::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(0);
#endif

    int N, M;
    cin >> N >> M;
    seg_tree segtree;
    segtree.init(N);

    for (int m = 0; m < M; ++m) {
        int type, a, b;
        cin >> type >> a >> b;
        --b;

        if (type == 1) {
            int v;
            cin >> v;
            segtree.update(a, b, v);
        } else {
            cout << segtree.query(a, b) << '\n';
        }
    }
}