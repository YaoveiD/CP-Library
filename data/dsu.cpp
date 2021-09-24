/*
*  author: yaoveil
*  date:   2021-06-22 23:13:08
*/

#include <bits/stdc++.h>

using namespace std;

// source : https://github.com/nealwu/competitive-programming
// verification : https://atcoder.jp/contests/practice2/submissions/26032473
struct union_find {
    // When data[x] < 0, x is a root and -data[x] is its tree size. When data[x] >= 0, data[x] is x's parent.
    vector<int> data;
    int n;
    int components = 0;

    union_find(int _n = -1) {
        if (_n >= 0)
            init(_n);
    }

    void init(int _n) {
        data.assign(_n + 1, -1);
        n = _n;
        components = _n;
    }

    int find(int x) {
        return data[x] < 0 ? x : data[x] = find(data[x]);
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }

    int get_size(int x) {
        return -data[find(x)];
    }

    bool unite(int x, int y) {
        x = find(x);
        y = find(y);

        if (x == y)
            return false;

        if (-data[x] < -data[y])
            swap(x, y);

        data[x] += data[y];
        data[y] = x;
        components--;
        return true;
    }

    vector<vector<int>> get_groups() {
        vector<int> parent(n), group_size(n);

        for (int i = 0; i < n; ++i) {
            parent[i] = find(i);
            group_size[parent[i]]++;
        }

        vector<vector<int>> result(n);

        for (int i = 0; i < n; ++i)
            result[i].reserve(group_size[i]);

        for (int i = 0; i < n; ++i)
            result[parent[i]].push_back(i);

        result.erase(
            remove_if(result.begin(), result.end(),
                    [&](const std::vector<int>& v) { return v.empty(); }),
            result.end());

        return result;
    }
};

//basic Dsu
class Dsu {
public:
  vector<int> p;
  int n;

  Dsu(int _n) : n(_n) {
    p.resize(n);
    iota(p.begin(), p.end(), 0);
  }

  inline int get(int x) {
    return (x == p[x] ? x : (p[x] = get(p[x])));
  }

  inline bool unite(int x, int y) {
    x = get(x);
    y = get(y);
    if (x != y) {
      p[x] = y;
      return true;
    }
    return false;
  }

  inline bool connected(int x, int y) {
    return get(x) == get(y);
  }
};

//unite by size ? but we can get the size of each component
class Dsu {
public:
  vector<int> p;
  vector<int> sz;
  int n, components;

  Dsu(int _n) : n(_n), components(_n) {
    p.resize(n);
    sz.resize(n);
    iota(p.begin(), p.end(), 0);
    fill(sz.begin(), sz.end(), 1);
  }

  inline int get(int x) {
    return (x == p[x] ? x : (p[x] = get(p[x])));
  }

  inline bool unite(int x, int y) {
    x = get(x);
    y = get(y);
    if (x != y) {
      if (x > y)
        swap(x, y);

      components -= 1;
      p[x] = y;
      sz[y] += sz[x];
      return true;
    }
    return false;
  }

  inline int size(int x) {
    x = get(x);
    return sz[x];
  }

  inline bool connected(int x, int y) {
    return get(x) == get(y);
  }

  inline int get_components() const {
    return components;
  }
};

//weighted
class Dsu {
public:
  int n;
  vector<int> p;
  vector<int> weight;

  Dsu(int _n) : n(_n) {
    p.resize(n);
    weight.resize(n);
    iota(p.begin(), p.end(), 0);
  }

  inline int get(int x) {
    if (x != p[x]) {
      int t = p[x];
      p[x] = get(p[x]);
      weight[x] += weight[t];
    }
    return p[x];
  }

  inline bool unite(int x, int y, int w = 0) {
    int px = get(x);
    int py = get(y);
    if (px != py) {
      p[px] = py;
      weight[px] = -weight[x] + weight[y] + w;
      return true;
    }
    // here should be some constraints
    return false;
  }
};
