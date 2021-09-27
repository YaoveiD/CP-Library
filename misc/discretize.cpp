// discretize a sequence of integers
template<typename T_iterable>
void discretize(T_iterable& seq, int start = 1) {
    T_iterable sorted = seq;
    sort(sorted.begin(), sorted.end());
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());

    for (auto&& item : seq) {
        item = lower_bound(sorted.begin(), sorted.end(), item) - sorted.begin() + start;
    }
}
