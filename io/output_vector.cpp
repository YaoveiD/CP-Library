template<typename T, char sep = ' '>
void output_vector(const vector<T>& v, bool add_one = false, int start = -1, int end = -1) {
    if (start < 0) start = 0;
    if (end < 0) end = int(v.size());

    for (int i = start; i != end; ++i)
        cout << (add_one ? v[i] + 1 : v[i]) << (i != end - 1 ? sep : '\n');
}
