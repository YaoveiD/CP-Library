// verification : https://leetcode-cn.com/problems/ipo/
// a basic segment tree

const int INF = (int) 1e9 + 123;

template<typename T>
class segtree {
private:
  //global actually
  #define ls i << 1 | 1
  #define rs (i << 1) + 2
public:
  struct node {
    int idx;
    T val;
    // TODO: don't forget to set a default value

    void apply(int _val, int _idx) {
        val = _val;
        idx = _idx;
    }
  };
  vector<node> tree;
  node identify;
  int N;

  segtree(int n) {
    N = n;

    int _N = 1;
    while (_N < n) {
      _N *= 2;
    }
    
    tree.resize(2 * _N - 1);
    build(0, 0, n - 1);
  }

  segtree(int n, vector<T>& A) {
    N = n;
    
    int _N = 1;
    while (_N < n) {
      _N *= 2;
    }
    
    tree.resize(_N * 2 - 1);
    build(0, 0, n - 1, A);
  }

  // TODO: combine two nodes
  inline node combine(const node& A, const node& B) {
    if (A.val > B.val) {
        return A;
    } else {
        return B;
    }
  }

  inline void pull(int i) {
    tree[i] = combine(tree[ls], tree[rs]);
  }

  void build(int i, int L, int R, vector<T>& A) {
    if (L == R) {
      tree[i].apply(A[L], L); // TODO: apply
      return;
    }
    
    int mid = L + (R - L) / 2;
    
    build(ls, L, mid, A);
    build(rs, mid + 1, R, A);
    
    pull(i);
  }

  void build(int i, int L, int R) {
    tree[i] = identify;
    
    if (L == R) {
      return;
    }
    
    int mid = L + (R - L) / 2;
    
    build(ls, L, mid);
    build(rs, mid + 1, R);
  }

  node query(int i, int from, int to, int L, int R) {
    if (to < L or from > R) {
      return identify; // Note: correctly set identify ?
    }
    
    if (L <= from and to <= R) {
      return tree[i];
    }
    
    int mid = (from + to) / 2;
    
    return combine(query(ls, from, mid, L, R), query(rs, mid + 1, to, L, R));
  }

  node query(int L, int R) {
    return query(0, 0, N - 1, L, R);
  }

  void update(int i, int from, int to, int L, int R, T val) {
    if (to < L or from > R) {
      return;
    }
    
    if (from == to) {
      tree[i].apply(val, from); // TODO: apply when 
      return;
    }
    
    int mid = (from + to) / 2;
    
    update(ls, from, mid, L, R, val);
    update(rs, mid + 1, to, L, R, val);
    
    pull(i);
  }

  void update(int L, int R, T val) {
    update(0, 0, N - 1, L, R, val);
  }

  void update(int p, T val) {
    update(0, 0 , N - 1, p, p, val);
  }
};
