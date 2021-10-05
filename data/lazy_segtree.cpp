#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>

using namespace std;

template<typename T>
class lazy_segtree {
private:
  //weird, global actually
  #define ls i << 1 | 1
  #define rs (i << 1) + 2
public:
  int N;
  struct node {
    T val, lazy;

    inline void apply(int from, int to, T d) {
      assert(from <= to);
      val += d * (to - from + 1);
      lazy += d;
    }
  };
  node identity;
  vector<node> tree;

  lazy_segtree(int n) {
    identity.val = 0;
    identity.lazy = 0;
    N = n;
    int _N = 1;
    while (_N < n) _N *= 2;
    tree.resize(_N * 2 - 1);
    build(0, 0, n - 1);
  }

  lazy_segtree(int n, const vector<T>& A) {
    identity.val = 0;
    identity.lazy = 0;
    assert(n > 0);
    N = n;
    int _N = 1;
    while (_N < n) _N *= 2;
    tree.resize(_N * 2 - 1);
    build(0, 0, n - 1, A);
  }

  inline node combine(const node& A, const node& B) {
    node C;
    C.val = A.val + B.val;
    return C;
  }

  inline void pull(int i) {
    tree[i] = combine(tree[ls], tree[rs]);
  }

  inline void push(int i, int from, int to) {
    if (tree[i].lazy != 0) {
      int mid = from + (to - from) / 2;
      tree[ls].apply(from, mid, tree[i].lazy);
      tree[rs].apply(mid + 1, to, tree[i].lazy);
      tree[i].lazy = 0;
    }
  }

  void build(int i, int L, int R) {
    tree[i].val = 0;
    tree[i].lazy = 0;
    if (L == R) {
      return;
    }
    int mid = L + (R - L) / 2;
    build(ls, L, mid);
    build(rs, mid + 1, R);
    // pull(i)
  }

  void build(int i, int L, int R, const vector<T>& A) {
    tree[i].val = 0;
    tree[i].lazy = 0;
    if (L == R) {
      tree[i].apply(L, R, A[L]);
      return;
    }
    int mid = L + (R - L) / 2;
    build(ls, L, mid, A);
    build(rs, mid + 1, R, A);
    pull(i);
  }

  void update(int i, int from, int to, int L, int R, T d) {
    if (to < L or from > R) {
      return;
    }
    if (L <= from and to <= R) {
      tree[i].apply(from, to, d);
      return;
    }
    push(i, from, to);
    int mid = from + (to - from) / 2;
    update(ls, from, mid, L, R, d);
    update(rs, mid + 1, to, L, R, d);
    pull(i);
  }

  void update(int L, int R, T d) {
    update(0, 0, N - 1, L, R, d);
  }

  void update(int pos, int d) {
    update(0, 0, N - 1, pos, pos, d);
  }

  node query(int i, int from, int to, int L, int R) {
    if (to < L or from > R) {
      return identity;
    }
    if (L <= from and to <= R) {
      return tree[i];
    }
    push(i, from, to);
    int mid = from + (to - from) / 2;
    return combine(query(ls, from, mid, L, R), query(rs, mid + 1, to, L, R)); 
  }

  T query(int L, int R) {
    return query(0, 0, N - 1, L, R).val;
  }

};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  
  int N, Q;
  cin >> N >> Q;
  vector<long long> A(N);
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
  }

  lazy_segtree<long long> st(N, A);
  
  string op;
  while (Q--) {
    int A, B;
    cin >> op >> A >> B;
    if (op == "Q") {
      cout << st.query(A - 1, B - 1) << '\n';
    } else {
      long long d;
      cin >> d;
      st.update(A - 1, B - 1, d);
    }
  }
  return 0;
}

// verification : https://atcoder.jp/contests/practice2/submissions/26367162

template<typename T>
class lazy_segtree {
private:
  //weird, global actually
  #define ls i << 1 | 1
  #define rs (i << 1) + 2
public:
  int N;
  struct node {
    int64_t zero = 0, one = 0;
    int64_t invs = 0;
    int has_change = 0;

    inline void apply(int from, int to) {
      assert(from <= to);
      has_change = !has_change;
      swap(zero, one);
      invs = one * zero - invs;
    }

    friend ostream& operator<<(ostream& os, const node& x) {
      os << x.zero << ' ' << x.one << ' ' << x.invs << ' ' << x.has_change;
      return os;
    }
  };
  node identity;
  vector<node> tree;

  lazy_segtree(int n, const vector<T>& A) {
    assert(n > 0);
    N = n;
    int _N = 1;
    while (_N < n) _N *= 2;
    tree.resize(_N * 2 - 1);
    build(0, 0, n - 1, A);
  }

  inline node combine(const node& A, const node& B) {
    node C;
    C.zero = A.zero + B.zero;
    C.one = A.one + B.one;
    C.invs = A.invs + B.invs + A.one * B.zero;
    return C;
  }

  inline void pull(int i) {
    tree[i] = combine(tree[ls], tree[rs]);
  }

  inline void push(int i, int from, int to) {
    if (tree[i].has_change) {
      int mid = (from + to) / 2;
      tree[ls].apply(from, mid);
      tree[rs].apply(mid + 1, to);
      tree[i].has_change = 0;
    }
  }

  void build(int i, int L, int R, const vector<T>& A) {
    if (L == R) {
      if (A[L] == 0) {
        tree[i].zero = 1;
      } else {
        tree[i].one = 1;
      }
      return;
    }
    int mid = L + (R - L) / 2;
    build(ls, L, mid, A);
    build(rs, mid + 1, R, A);
    pull(i);
  }

  void update(int i, int from, int to, int L, int R) {
    if (to < L or from > R) {
      return;
    }
    if (L <= from and to <= R) {
      tree[i].apply(from, to);
      return;
    }
    push(i, from, to);
    int mid = from + (to - from) / 2;
    update(ls, from, mid, L, R);
    update(rs, mid + 1, to, L, R);
    pull(i);
  }

  void update(int L, int R) {
    update(0, 0, N - 1, L, R);
  }

  node query(int i, int from, int to, int L, int R) {
    if (to < L or from > R) {
      return identity;
    }
    if (L <= from and to <= R) {
      return tree[i];
    }
    push(i, from, to);
    int mid = from + (to - from) / 2;
    return combine(query(ls, from, mid, L, R), query(rs, mid + 1, to, L, R));
  }

  node query(int L, int R) {
    return query(0, 0, N - 1, L, R);
  }
};

void solve() {
    int N, Q;
    cin >> N >> Q;

    vector<int> A(N);
    for (int& a : A)
        cin >> a;

    lazy_segtree<int> st(N, A);

    while (Q--) {
        int type, L, R;
        cin >> type >> L >> R;
        --L; --R;

        if (type == 1) {
            st.update(L, R);
        } else {
            cout << st.query(L, R).invs << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(0);
#endif

    solve();

    return 0;
}