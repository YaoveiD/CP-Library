// Compresses the values in arr to be in the range [start, n + start).
template<typename T>
vector<int> compress_array(const vector<T> &arr, int start = 0) {
    int n = int(arr.size());
    vector<T> sorted = arr;
    sort(sorted.begin(), sorted.end());
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
    vector<int> compressed(n);

    for (int i = 0; i < n; i++)
        compressed[i] = int(lower_bound(sorted.begin(), sorted.end(), arr[i]) - sorted.begin()) + start;

    return compressed;
}
