#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
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

// verification: https://atcoder.jp/contests/practice2/submissions/26093709
// kind of slow I think

const int INF = int(1e9) + 5;

template<typename T>
class segtree {
private:
  //global actually
  #define ls i << 1 | 1
  #define rs (i << 1) + 2
public:
  struct segment {
    T val;

    // TODO: default value should be identity
    segment(T _val = INF) {}

    void apply(T _val) {
      val = _val;
    }
  };

  vector<segment> tree;
  segment identify;
  int N;

  segtree(int n) {
    init(n);
  }

  template<typename U>
  segtree(int n, vector<U>& A) {
    init(n);
    build(0, 0, n - 1, A);
  }

  void init(int n) {
    N = n;
    int _N = 1;
    while (_N < n)
      _N *= 2;
    tree.assign(2 * _N - 1, segment()); // or 4*N?
  }

  // TODO: combine two segments
  inline segment combine(const segment& A, const segment& B) {
    return A.val > B.val ? A : B;
  }

  inline void pull(int i) {
    tree[i] = combine(tree[ls], tree[rs]);
  }

  template<typename U>
  void build(int i, int L, int R, vector<U>& A) {
    if (L == R) {
      tree[i].apply(A[L]); // TODO: apply initial
      return;
    }
    
    int mid = L + (R - L) / 2;
    
    build(ls, L, mid, A);
    build(rs, mid + 1, R, A);
    
    pull(i);
  }

  // [L, R]
  segment query(int i, int from, int to, int L, int R) {
    if (to < L or from > R) {
      return identify; // Note: correctly set identify ?
    }
    
    if (L <= from and to <= R) {
      return tree[i];
    }
    
    int mid = (from + to) / 2;
    
    return combine(query(ls, from, mid, L, R), query(rs, mid + 1, to, L, R));
  }

  segment query(int L, int R) {
    return query(0, 0, N - 1, L, R);
  }

  // [L, R] consider using lazy segment tree?
  void update(int i, int from, int to, int L, int R, T val) {
    if (to < L or from > R) {
      return;
    }
    
    if (from == to) {
      tree[i].apply(val); // TODO: apply range change
      return;
    }
    
    int mid = (from + to) / 2;
    
    update(ls, from, mid, L, R, val);
    update(rs, mid + 1, to, L, R, val);
    
    pull(i);
  }

  // update single
  void update(int i, int from, int to, int p, T val) {
    if (from == to) {
      tree[i].apply(val); // TODO: apply single change
      return;
    }

    int mid = (from + to) / 2;

    if (p <= mid) {
      update(ls, from, mid, p, val);
    } else {
      update(rs, mid + 1, to, p, val);
    }

    pull(i);
  }

  void update(int L, int R, T val) {
    update(0, 0, N - 1, L, R, val);
  }

  // update single
  void update(int p, T val) {
    update(0, 0, N - 1, p, val);
  }
// }; // basic segtree

  int find_first_knowingly(int i, int from, int to, int L, int R, const function<bool(const segment&)>& func) {
    if (!func(tree[i])) {
      return -1;
    }

    if (from > R or to < L) {
      return -1;
    }

    if (from == to) {
      return from;
    }

    int mid = (from + to) / 2;
    int index = find_first_knowingly(ls, from, mid, L, R, func);
    if (index == -1) {
      index = find_first_knowingly(rs, mid + 1, to, L, R, func);
    }

    return index;
  }

  int find_first(int L, int R, const function<bool(const segment&)>& func) {
    return find_first_knowingly(0, 0, N - 1, L, R, func);
  }

  int find_first(const function<bool(const segment&)>& func) {
    return find_first_knowingly(0, 0, N - 1, 0, N - 1, func);
  }

  int find_last_knowingly(int i, int from, int to, int L, int R, const function<bool(const segment&)>& func) {
    if (!func(tree[i])) {
      return -1;
    }

    if (from > R or to < L) {
      return -1;
    }

    if (from == to) {
      return from;
    }

    int mid = (from + to) / 2;
    int index = find_first_knowingly(rs, mid + 1, to, L, R, func);
    if (index == -1) {
      index = find_first_knowingly(ls, from, mid, L, R, func);
    }

    return index;
  }

  int find_last(int L, int R, const function<bool(const segment&)>& func) {
    return find_last_knowingly(0, 0, N - 1, L, R, func);
  }

  int find_last(const function<bool(const segment&)>& func) {
    return find_last_knowingly(0, 0, N - 1, 0, N - 1, func);
  }

};
