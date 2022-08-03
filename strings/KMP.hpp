struct KMP {
    std::vector<int> next;

    void get_next(const std::string& S) {
        int N = int(S.size());
        next.resize(N);
        int cur = 0, i = 1;
        next[0] = 0;

        while (i < N) {
            if (S[cur] == S[i]) {
                next[i++] = ++cur;
            } else if (cur != 0) {
                cur = next[cur - 1];
            } else {
                next[i++] = 0;
            }
        }
    }

    // Count how many substrings in `S` equal `T` in O(|S| + |T|).
    int kmp(const std::string& S, const std::string& T) {
        int matches = 0;
        int N = int(S.size()), M = int(T.size());
        int i = 0, j = 0;
        get_next(T);
    
        while (i < N) {
            if (S[i] == T[j]) {
                i++; j++;
            } else if (j != 0) {
                j = next[j - 1];
            } else {
                i++;
            }
            if (j == M) {
                matches++;
                j = next[j - 1];
            }
        }
    
        return matches;
    }
};
