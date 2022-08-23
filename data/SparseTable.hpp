template<typename T, typename T_func = std::function<T(const T&, const T&)>>
struct sparse_table {
    int n;
    std::vector<std::vector<T>> table;
    T_func func;

    sparse_table(const std::vector<T> &a, const T_func &f) : table(1, a), func(f) {
        n = int(a.size());
        int levels = 32 - __builtin_clz(n);

        for (int j = 1; j < levels; j++) {
            table.emplace_back(n - (1 << j) + 1);

            for (int i = 0; i <= n - (1 << j); i++)
                table[j][i] = func(table[j - 1][i], table[j - 1][i + (1 << (j - 1))]);
        }
    }

    // [a, b)
    T query(int a, int b) const {
        assert(0 <= a && a < b && b <= n);
        int level = 31 - __builtin_clz(b - a);
        return func(table[level][a], table[level][b - (1 << level)]);
    }
};
