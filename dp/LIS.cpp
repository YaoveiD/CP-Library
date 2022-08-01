template<typename T>
int LIS(const std::vector<T> &sequence) {
    std::vector<T> d;

    for (const auto &x : sequence) {
        auto it = lower_bound(d.begin(), d.end(), x);

        if (it == d.end()) {
            d.push_back(x);
        } else {
            *it = x;
        }
    }

    return int(d.size());
}
