template <typename T, typename T_func = function<T(const T&, const T&)>>
struct sparse_table {
    int n;
    vector<vector<T>> ranges;
    T_func func;
 
    sparse_table(const vector<T> &a, const T_func &f) : ranges(1, a), func(f) {
        n = static_cast<int>(a.size());
        int levels = 32 - __builtin_clz(n);
        for (int j = 1; j < levels; j++) {
            ranges.emplace_back(n - (1 << j) + 1);
            for (int i = 0; i <= n - (1 << j); i++)
                ranges[j][i] = func(ranges[j - 1][i], ranges[j - 1][i + (1 << (j - 1))]);
        }
    }
 
    // [a, b)
    T query(int a, int b) const {
        assert(0 <= a && a < b && b <= n);
        int level = 31 - __builtin_clz(b - a);
        return func(ranges[level][a], ranges[level][b - (1 << level)]);
    }
};
