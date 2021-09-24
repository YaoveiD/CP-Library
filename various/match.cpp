template<typename T_iterable>
bool match(const T_iterable& text, const T_iterable& pat) {
    int i = 0, j = 0;

    while (i < (int) text.size() and j < (int) pat.size()) {
        if (text[i] == pat[j])
            ++i, ++j;
        else
            ++i;
    }

    return j == (int) pat.size();
}