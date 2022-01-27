template<typename T_array>
bool match(const T_array& text, const T_array& pat) {
    int i = 0, j = 0, n = int(text.size()), m = int(pat.size());

    while (i < n && j < m) {
        if (text[i] == pat[j])
            ++i, ++j;
        else
            ++i;
    }

    return j == m;
}