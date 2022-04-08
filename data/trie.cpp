/*
*  author:  yaoveil
*  created: 2021-08-08 23:42:47
*/
#include <bits/stdc++.h>
using namespace std;

struct Trie {
    struct node {
        array<int, 2> child;
        int words = 0;

        node() {
            child.fill(-1);
        }
    };

    static const int BITS = 30;
    static const int ROOT = 0;
    vector<node> nodes = {node()};

    Trie(int n = 0) {
        nodes.reserve(BITS * n);
    }

    int get_or_create_node(int node, int c) {
        if (nodes[node].child[c] < 0) {
            nodes[node].child[c] = int(nodes.size());
            nodes.emplace_back();
        }

        return nodes[node].child[c];
    }

    int insert(int value) {
        int node = ROOT;

        for (int i = BITS; i >= 0; --i)
            node = get_or_create_node(node, value >> i & 1);
        
        nodes[node].words++;
        return node;
    }

    int query_max_xor(int value) {
        int result = 0;
        int node = ROOT;

        for (int i = BITS; i >= 0 && node != -1; --i) {
            int b = value >> i & 1;

            if (nodes[node].child[!b] > 0) {
                result |= 1 << i;
                node = nodes[node].child[!b];
            } else {
                node = nodes[node].child[b];
            }
        }

        return result;
    }
};

// Solution to : https://www.acwing.com/problem/content/3488/
// Maximum xor of two numbers in an array.

int main() {
    ios::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(0);
#endif

    int N;
    cin >> N;
    Trie trie;
    int ans = 0;

    for (int i = 0; i < N; ++i) {
        int a;
        cin >> a;
        ans = max(ans, trie.query_max_xor(a));
        trie.insert(a);
    }

    cout << ans << '\n';
}
