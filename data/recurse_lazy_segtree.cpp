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
#define debug(...) cerr << "[" << #__VA_AendGS__ << "]:", debug_out(__VA_AendGS__)
#else
#define debug(...) 
#endif

// solution to https://codeforces.com/edu/course/2/lesson/5/3/practice/status
// this data structure can handle the follow two operations
// 1. set v to to all elements on the segment from l to r
// 2. find the segment with maximal sum

const int SENTINEL = -1000000009;

struct segment_change {
    int64_t to_set;

    segment_change(int64_t _set = SENTINEL) : to_set(_set) {}

    bool has_change() const {
        return to_set != SENTINEL;
    }

    void combine(const segment_change& other) {
        to_set = other.to_set;
    }
};

struct segment {
    int64_t sum, prefix_max, suffix_max, mx;

    segment(int64_t value = 0) : sum(value), prefix_max(value), suffix_max(value), mx(value) {}

    void apply(int length, const segment_change& change) {
        sum = change.to_set * length;
        prefix_max = max<int64_t>(0, sum);
        suffix_max = prefix_max;
        mx = prefix_max;
    }
};

// combine two segments
// consider to rewrite this for better performance
segment join(const segment& a, const segment& b) {
    segment c;
    c.sum = a.sum + b.sum;
    c.prefix_max = max(a.prefix_max, a.sum + b.prefix_max);
    c.suffix_max = max(b.suffix_max, b.sum + a.suffix_max);
    c.mx = max({a.suffix_max + b.prefix_max, a.mx, b.mx});
    return c;
}

const segment identity;

struct seg_tree {
    int tree_n;
    vector<segment> tree;
    vector<segment_change> changes;

    seg_tree(int n = -1) {
        if (n > 0)
            init(n);
    }

    // full 
    void init(int _n) {
        tree_n = 1;
        while (tree_n < _n) tree_n *= 2;
        tree.assign(tree_n * 2, segment());
        changes.assign(tree_n, segment_change());
    }

    // apply the change on segment and combine the changes
    void apply_and_combine(int p, int length, const segment_change& change) {
        tree[p].apply(length, change);

        if (p < tree_n)
            changes[p].combine(change);
    }

    // push up left and right segments
    void pull(int p) {
        tree[p] = join(tree[p * 2], tree[p * 2 + 1]);
    }

    // push down the segment change
    void push(int p, int length) {
        if (changes[p].has_change()) {
            apply_and_combine(p * 2, length / 2, changes[p]);
            apply_and_combine(p * 2 + 1, length / 2, changes[p]);
            changes[p] = segment_change();
        }
    }

    // Builds our tree from an array in O(tree_n).
    void build(const vector<segment> &initial) {
        int n = int(initial.size());
        init(n);
        assert(n <= tree_n);

        for (int i = 0; i < n; i++)
            tree[tree_n + i] = initial[i];

        for (int position = tree_n - 1; position > 0; position--)
            tree[position] = join(tree[2 * position], tree[2 * position + 1]);
    }

    void update(int p, int start, int end, int a, int b, const segment_change& change) {
        if (a <= start && end <= b) {
            apply_and_combine(p, end - start + 1, change); // Note : don't use apply
            return;
        }

        if (b < start || a > end)
            return;

        push(p, end - start + 1);
        int mid = (start + end) / 2;
        update(p * 2, start, mid, a, b, change);
        update(p * 2 + 1, mid + 1, end, a, b, change);
        pull(p);
    }

    // Note: [a, b]
    void update(int a, int b, const segment_change& change) {
        update(1, 0, tree_n - 1, a, b, change);
    }

    segment query(int p, int start, int end, int a, int b) {
        if (a <= start && end <= b) {
            return tree[p];
        }

        if (b < start || a > end)
            return identity;

        push(p, end - start + 1);
        int mid = (start + end) / 2;
        return join(query(p * 2, start, mid, a, b), query(p * 2 + 1, mid + 1, end, a, b));
    }

    // Note: [a, b]
    // consider to change the return type for better performance
    segment query(int a, int b) {
        return query(1, 0, tree_n - 1, a, b);
    }

// }; // basic lazy segment tree.

    template<typename T_bool>
    int find_first(int p, int start, int end, int a, T_bool&& pred) {
        if (!pred(tree[p]) || end < a)
            return -1;

        if (start == end) 
            return start;

        push(p, end - start + 1);
        int mid = start + (end - start) / 2;
        int index = -1;

        if (pred(tree[p * 2]))
            index = find_first(p * 2, start, mid, a, pred);
        else
            index = find_first(p * 2 + 1, mid + 1, end, a, pred);

        return index;
    }

    // find first element returns true on segment [a, tree_n)
    template<typename T_bool>
    int find_first(int a, T_bool&& pred) {
        return find_first(1, 0, tree_n - 1, a, pred);
    }
};

int main() {
    ios::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(0);
#endif

    int N, M;
    cin >> N >> M;
    seg_tree segtree(N);

    while (M--) {
        int a, b, v;
        cin >> a >> b >> v;
        segtree.update(a, b - 1, segment_change(v));
        cout << segtree.query(0, N - 1).mx << '\n';
    }
}