/*
*  author:  yaoveil
*  created: 2021-08-08 23:42:47
*/

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

class Trie {
public:
  struct node {
    int val, cnt;
    int next[2];
  };
  vector<node> tree;
  int node_count;

  Trie(int n) {
    tree.resize(n * 31);
    node_count = 0;
    for (auto& x : tree) {
      x.val = x.cnt = x.next[1] = x.next[0] = 0;
    }
  }

  void insert(int val, int delta) {
    int p = 0;
    for (int i = 30; i >= 0; --i) {
      int bit = (val >> i) & 1;
      if (!tree[p].next[bit]) {
        tree[p].next[bit] = ++node_count;
      }
      p = tree[p].next[bit];
      tree[p].cnt += delta;
    }
  }

  int query(int x) {
    int ret = 0;
    int p = 0;
    for (int i = 30; i >= 0; --i) {
      int bit = (x >> i) & 1;
      if (tree[tree[p].next[!bit]].cnt) {
        ret += (1 << i);
        p = tree[p].next[!bit];
      } else {
        p = tree[p].next[bit];
      }
    }
    return ret;
  }

};

/*
  the maximum xor segment with the length at most M
*/

// make sure to intialize all global vars
// uncomment cin >> tt?
void solve() {
  int N, M;
  cin >> N >> M;
  vector<int> A(N);
  vector<int> prefix_xor(N + 1);
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
    prefix_xor[i + 1] = prefix_xor[i] ^ A[i];
  }

  Trie trie(N);
  trie.insert(0, 1);
  int ans = 0;
  for (int i = 1; i <= N; ++i) {
    if (i > M) {
      trie.insert(prefix_xor[i - M - 1], -1);
    }
    ans = max(ans, trie.query(prefix_xor[i]));
    trie.insert(prefix_xor[i], 1);
  }
  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int tt = 1;
  // cin >> tt;
  while (tt--) {
    solve();
  }

  return 0;
}
