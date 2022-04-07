// 2D fenwick tree
// source : https://github.com/the-tourist/algo/blob/master/data/fenwick2d.cpp
// 0-indexed

template <typename T>
class fenwick2d {
public:
  vector<vector<T>> fenw;
  int n, m;
  fenwick2d(int _n, int _m) : n(_n), m(_m) {
    fenw.resize(n);
    for (int i = 0; i < n; i++) {
      fenw[i].resize(m);
    }
  }
  inline void modify(int i, int j, T v) {
    int x = i;
    while (x < n) {
      int y = j;
      while (y < m) {
        fenw[x][y] += v;
        y |= (y + 1);
      }
      x |= (x + 1);
    }
  }
  // close
  inline T get(int i, int j) {
    T v{};
    int x = i;
    while (x >= 0) {
      int y = j;
      while (y >= 0) {
        v += fenw[x][y];
        y = (y & (y + 1)) - 1;
      }
      x = (x & (x + 1)) - 1;
    }
    return v;
  }
  // close
  inline T query(int a, int b, int c, int d) {
    return get(c, d) - get(a - 1, d) - get(c, b - 1) + get(a - 1, b - 1);
  }
};

// struct node {
//   int a = ...; // don't forget to set default value
//   inline void operator += (node &other) {
//     ...
//   }
// };

int main() {
    fenwick2d<int> tree(4, 3);

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            tree.modify(i, j, 1);
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            tree.modify(i, j, 1);

/**
 * 2 2 2
 * 2 2 2
 * 2 2 2
 * 2 2 2
 **/

    cout << tree.get(1, 1) << '\n';
    cout << tree.get(0, 2) << '\n';
    cout << tree.query(1, 1, 1, 1) << '\n';
    cout << tree.query(0, 0, 3, 2) << '\n';
}