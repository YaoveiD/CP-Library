#include <bits/stdc++.h>
using namespace std;

// solution to https://codeforces.com/edu/course/2/lesson/5/3/practice/status
// this data structure can handle the following two operations
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
segment combine(const segment& a, const segment& b) {
    segment c;
    c.sum = a.sum + b.sum;
    c.prefix_max = max(a.prefix_max, a.sum + b.prefix_max);
    c.suffix_max = max(b.suffix_max, b.sum + a.suffix_max);
    c.mx = max({a.suffix_max + b.prefix_max, a.mx, b.mx});
    return c;
}

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
        tree[p] = combine(tree[p * 2], tree[p * 2 + 1]);
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
            tree[position] = combine(tree[2 * position], tree[2 * position + 1]);
    }

    void update(int p, int start, int end, int a, int b, const segment_change& change) {
        if (a <= start && end <= b) {
            apply_and_combine(p, end - start, change);
            return;
        }

        if (b <= start || a >= end)
            return;

        push(p, end - start);
        int mid = (start + end) / 2;
        update(p * 2, start, mid, a, b, change);
        update(p * 2 + 1, mid, end, a, b, change);
        pull(p);
    }

    // Note: [a, b)
    void update(int a, int b, const segment_change& change) {
        update(1, 0, tree_n, a, b, change);
    }

    segment query(int p, int start, int end, int a, int b) {
        if (a <= start && end <= b) {
            return tree[p];
        }

        if (b <= start || a >= end)
            return segment();

        push(p, end - start);
        int mid = (start + end) / 2;
        return combine(query(p * 2, start, mid, a, b), query(p * 2 + 1, mid, end, a, b));
    }

    // Note: [a, b)
    // consider to change the return type for better performance
    segment query(int a, int b) {
        return query(1, 0, tree_n, a, b);
    }

// }; // basic lazy segment tree.

    template<typename T_bool>
    int find_first(int p, int start, int end, int a, T_bool&& pred) {
        if (!pred(tree[p]) || end <= a)
            return -1;

        if (start == end - 1) 
            return start;

        push(p, end - start);
        int mid = (start + end) / 2;
        int index = -1;

        if (pred(tree[p * 2]))
            index = find_first(p * 2, start, mid, a, pred);
        
        if (index == -1) // I don't know
            index = find_first(p * 2 + 1, mid, end, a, pred);

        return index;
    }

    // find first element returns true on segment [a, tree_n)
    template<typename T_bool>
    int find_first(int a, T_bool&& pred) {
        return find_first(1, 0, tree_n, a, pred);
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
        segtree.update(a, b, segment_change(v));
        cout << segtree.query(0, N).mx << '\n';
    }
}