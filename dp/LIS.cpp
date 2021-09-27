
template<typename iterable_T>
vector<int> LIS(const iterable_T sequence) {
    int n = int(sequence.size());

    assert(n > 0);

    vector<int> d(n + 1, int(1e9));
    vector<int> result(n);

    d[0] = -int(1e9);
    for (int i = 0; i < n; ++i) {
        auto it = lower_bound(d.begin(), d.end(), sequence[i]);
        result[i] = int(it - d.begin());
        *it = sequence[i];
    }

    return result;
}
