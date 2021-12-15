// source : https://github.com/nealwu/competitive-programming/blob/master/bst/orderset-pbds.cc
// Solution to https://www.spoj.com/problems/ORDERSET/
#include <iostream>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

// WARNING: functions as a set (doesn't allow duplicates); insert pairs instead if duplicates are needed.
// Consider using splay_tree instead if constant factor is an issue (e.g., log^2 solutions), especially with duplicates.
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;


// index is in [0, tree_n)
struct fenwick_tree {
    int tree_n, log_n;
    vector<int> tree;

    static int highest_bit(int x) {
        return x == 0 ? -1 : 31 - __builtin_clz(x);
    }

    fenwick_tree(int n) : tree_n(n), log_n(highest_bit(n) + 1), tree(n + 1) {}

    bool update(int p, int x) {
        if (tree[p + 1] + x < 0)
            return false;

        for (p += 1; p <= tree_n; p += p & -p)
            tree[p] += x;

        return true;
    }

    int query(int p) {
        int sum = 0;

        for (p += 1; p > 0; p -= p & -p)
            sum += tree[p];

        return sum;
    }

    int find_by_order(int order) {
        int current = 0;
        int index = 0;
        order++;

        for (int i = log_n; i >= 0; --i) {
            if (index + (1 << i) <= tree_n && current + tree[index + (1 << i)] < order) {
                index += (1 << i);
                current += tree[index];
            }
        }

        return index;
    }

    // Note : returns the order of the first element of key.
    int order_of_key(int key) {
        return query(key - 1);
    }
};

int main() {
    int Q;
    scanf("%d", &Q);
    ordered_set<int> values;
    fenwick_tree tree(100);

    for (int q = 0; q < Q; q++) {
        char op;
        int x;
        scanf(" %c %d", &op, &x);

        if (op == 'I') {
            values.insert(x);
            tree.update(x, +1);
        } else if (op == 'D') {
            values.erase(x);
            tree.update(x, -1);
        } else if (op == 'K') {
            x--;

            if (x >= int(values.size()))
                puts("invalid");
            else {
                // find_by_order(x) gives the x-th element in sorted order; if x = 2, gives the third smallest value.
                printf("%d %d\n", *values.find_by_order(x), tree.find_by_order(x));
            }
        } else if (op == 'C') {
            // order_of_key(x) returns the count of elements < x.
            printf("%d %d\n", int(values.order_of_key(x)), tree.order_of_key(x));
        }
    }
}
