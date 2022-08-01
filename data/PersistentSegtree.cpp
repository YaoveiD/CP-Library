#include <bits/stdc++.h>

const int RESERVE_SIZE = 200005;

/* data type for individual
* node in the segment tree */
struct node {
    // stores sum of the elements in node
    int val = 0;

    // pointer to left and right children
    node* left = nullptr, *right = nullptr;

    // required constructors........
    node() {}
    node(node* l, node* r, int v) : val(v), left(l), right(r) {}
};

int v[RESERVE_SIZE];

// root pointers for all versions
node* version[RESERVE_SIZE];

// Constructs Version-0
// Note : [low, high)
void build(node* n, int low, int high) {
    if (low + 1 == high)
        return;

    int mid = (low + high) / 2;
    n->left = new node(nullptr, nullptr, 0);
    n->right = new node(nullptr, nullptr, 0);
    build(n->left, low, mid);
    build(n->right, mid, high);
    n->val = n->left->val + n->right->val;
}

/**
* Note: `Upgrade` assign value to arr[idx] in version cur
* Note : [low, high)
* Upgrades to new Version
* @param prev : points to node of previous version
* @param cur : points to node of current version
* Time Complexity : O(logn)
* Space Complexity : O(logn) */
void upgrade(node* prev, node* cur, int low, int high,
            int idx, int value) {
    if (idx >= high || idx < low || low >= high)
        return;

    if (low + 1 == high) {
        // modification in new version
        cur->val = value;
        return;
    }

    int mid = (low + high) / 2;
    if (idx < mid) {
        // link to right child of previous version
        cur->right = prev->right;
        // create new node in current version
        cur->left = new node(nullptr, nullptr, 0);
        upgrade(prev->left, cur->left, low, mid, idx, value);
    } else {
        // link to left child of previous version
        cur->left = prev->left;
        // create new node for current version
        cur->right = new node(nullptr, nullptr, 0);
        upgrade(prev->right, cur->right, mid, high, idx, value);
    }

    // calculating data for current version
    // by combining previous version and current
    // modification
    cur->val = cur->left->val + cur->right->val;
}

// Returns the sum of the range [l, r)
int query(node* n, int low, int high, int l, int r) {
    if (l >= high || r <= low || low >= high)
        return 0;
    if (l <= low && high <= r)
        return n->val;
    int mid = (low + high) / 2;
    int p1 = query(n->left, low, mid, l, r);
    int p2 = query(n->right, mid, high, l, r);
    return p1 + p2;
}

int main() {
    using namespace std;
    int N; cin >> N; getchar();
    version[0] = new node();
    build(version[0], 0, N);
    int cv = 0;

    for (int i = 1; i <= N; ++i) {
        string str; getline(cin, str);
        bool neg = false;
        bool has = false;
        int val = 0;

        for (int j = 0; j < int(str.size()); ++j) {
            if (str[j] == '-') {
                has = neg = true;
            } else if (str[j] == '+') {
                has = true;
            } else if (str[j] == ' ') {
                int num = neg ? 0 : 1;
                version[++cv] = new node();
                upgrade(version[cv-1], version[cv], 0, N, val, num);
                val = 0;
                neg = false;
            } else {
                val = val * 10 + str[j] - '0';
            }
        }

        if (has) {
            int num = neg ? 0 : 1;
            version[++cv] = new node();
            upgrade(version[cv-1], version[cv], 0, N, val, num);
        }

        v[i] = cv;
    }

    int x = 0;

    for (int i = 0; i < N; ++i) {
        int D; cin >> D;

        if (D == 0)
            continue;

        node *n = version[v[D]];
        int a = query(n, 0, N, 0, N);
        int b = query(n, 0, N, 0, x);
        x = (x + a - b) % N;
    }

    cout << x << '\n';
}
