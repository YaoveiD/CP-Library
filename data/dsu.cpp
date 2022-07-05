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
// }; // basic union_find

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