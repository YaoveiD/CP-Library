#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

// since POJ is such an OLD_B_DENG, I wirte this C style code
// verification : http://poj.org/showsource?solution_id=23033753   Memory: 12356K Time: 1282MS

const int SIZE = 100005;

int N;
int ts;
vector<vector<int>> tree(SIZE*2);
int tin[SIZE], tout[SIZE];
int have[SIZE];
int fenwick[SIZE];

inline int lowbit(int x) {
    return x & -x;
}

void update(int p, int change) {
    while (p <= N) {
        fenwick[p] += change;
        p += lowbit(p);
    }
}

int query(int p) {
    int result = 0;
    
    while (p) {
        result += fenwick[p];
        p -= lowbit(p);
    }
    
    return result;
}

inline int query(int a, int b) {
    return query(b) - query(a - 1);
}

void dfs(int v, int p) {
    tin[v] = ++ts;

    for (int i = 0; i < (int) tree[v].size(); ++i) if (tree[v][i] != p) {
        dfs(tree[v][i], v);
    }

    tout[v] = ts;
}

int main() {
    scanf("%d", &N);

    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        --u; --v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    dfs(0, -1);

    for (int t = 0; t < N; ++t) {
        update(t + 1, 1);
        have[t] = 1;
    }

    int M;
    scanf("%d", &M);

    while (M--) {
        char op;
        int x;
        scanf(" %c %d", &op, &x);
        --x;

        if (op == 'Q') {
            cout << query(tin[x], tout[x]) << '\n';
        } else {
            update(tin[x], have[x] ? -1 : +1);
            have[x] ^= 1;
        }
    }
}