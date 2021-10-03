// verification: https://atcoder.jp/contests/practice2/submissions/26093709

template<typename T>
class segtree {
private:
  //global actually
  #define ls i << 1 | 1
  #define rs (i << 1) + 2
public:
  struct node {
    T val = INF;
    // TODO: don't forget to set a default value

    void apply(int _val) {
        val = _val;
    }
  };
  vector<node> tree;
  static const node identify;
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
    return A.val > B.val ? A : B;
  }

  inline void pull(int i) {
    tree[i] = combine(tree[ls], tree[rs]);
  }

  void build(int i, int L, int R, vector<T>& A) {
    if (L == R) {
      tree[i].apply(A[L]); // TODO: apply
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
      tree[i].apply(val); // TODO: apply when 
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

  int find_first_knowingly(int i, int from, int to, int L, int R, const function<bool(const node&)>& func) {
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

  int find_first(int L, int R, const function<bool(const node&)>& func) {
    return find_first_knowingly(0, 0, N - 1, L, R, func);
  }

  int find_first(const function<bool(const node&)>& func) {
    return find_first_knowingly(0, 0, N - 1, 0, N - 1, func);
  }

  int find_last_knowingly(int i, int from, int to, int L, int R, const function<bool(const node&)>& func) {
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

  int find_last(int L, int R, const function<bool(const node&)>& func) {
    return find_last_knowingly(0, 0, N - 1, L, R, func);
  }

  int find_last(const function<bool(const node&)>& func) {
    return find_last_knowingly(0, 0, N - 1, 0, N - 1, func);
  }

};
