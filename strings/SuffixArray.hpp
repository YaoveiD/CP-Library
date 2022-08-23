template<typename T> struct RMQ {
    std::vector<std::vector<T>> mat;

    void build(const std::vector<T> &V) {
        mat.assign(1, V);
        for (int pw = 1, k = 1; pw * 2 <= int(V.size()); pw *= 2, ++k) {
            mat.emplace_back(int(V.size()) - pw * 2 + 1);
            for (int j = 0; j < int(mat[k].size()); ++j)
                mat[k][j] = std::min(mat[k - 1][j], mat[k - 1][j + pw]);
        }
    }

    T query(int a, int b) const {
        assert(a < b); // or return `inf` if a == b
        int dep = 31 - __builtin_clz(b - a);
        return std::min(mat[dep][a], mat[dep][b - (1 << dep)]);
    }
};

struct suffix_array {
    int n;
    std::vector<int> suffix, rank;
    std::vector<int> lcp;
    std::string str;
    RMQ<int> rmq;

    suffix_array(const std::string &_str) {
        build(_str);
        rmq.build(lcp);
    }

    void build(const std::string &_str) {
        str = _str;
        n = int(str.size());
        suffix.resize(n);
        std::vector<int> freq(128);
        for (char c : str) freq[c]++;

        for (int c = 1; c < 128; ++c)
            freq[c] += freq[c-1];

        for (int i = 0; i < n; ++i)
            suffix[--freq[str[i]]] = i;

        rank.resize(n);
        rank[suffix[0]] = 0;

        for (int i = 1; i < n; ++i)
            rank[suffix[i]] = str[suffix[i]] == str[suffix[i-1]] ? rank[suffix[i-1]] : i;

        for (int len = 1; len < n; len *= 2) {
            std::vector<int> next_index(n);
            std::iota(next_index.begin(), next_index.end(), 0);
            std::vector<int> nsuffix(n);

            // i + len >= n goes first
            for (int i = n - len; i < n; ++i)
                nsuffix[next_index[rank[i]]++] = i;

            for (int i = 0; i < n; ++i) {
                int before = suffix[i] - len;
                if (before >= 0) nsuffix[next_index[rank[before]]++] = before;
            }

            suffix.swap(nsuffix);
            std::vector<int> nrank(n);
            bool done = true;

            for (int i = 1; i < n; ++i) {
                int s = suffix[i], b = suffix[i-1];

                if (std::max(s, b) + len < n && rank[s] == rank[b] && rank[s+len] == rank[b+len]) {
                    done = false;
                    nrank[s] = nrank[b];
                } else {
                    nrank[s] = i;
                }
            }

            rank.swap(nrank);
            if (done) break;
        }

        compute_lcp();
    }

    void compute_lcp() {
        lcp.resize(n);
        int match = 0;

        // iterate over the suffixes from the longest to the shortest
        for (int i = 0; i < n; ++i) {
            if (rank[i] == 0)
                continue;

            int a = suffix[rank[i]] + match;
            int b = suffix[rank[i] - 1] + match;

            while (a < n && b < n && str[a++] == str[b++])
                match++;

            // lcp[r] = the longest common prefix length of the suffixes starting at suffix[r] and at suffix[r - 1].
            // Note that lcp[0] is always 0.
            lcp[rank[i]] = match;
            match = std::max(match - 1, 0);
        }
    }

    int get_lcp(int a, int b) const {
        if (a >= n || b >= n)
            return 0;

        if (a == b)
            return n - a;

        a = rank[a], b = rank[b];
        if (a > b) std::swap(a, b);
        return rmq.query(a + 1, b + 1);
    }

    // Compares the substrings starting at `a` and `b` up to `length` in O(1).
    int compare(int a, int b, int length = -1) const {
        if (length < 0)
            length = n;

        if (a == b)
            return 0;

        int common = get_lcp(a, b);

        if (common >= length)
            return 0;

        if (a + common >= n || b + common >= n)
            return a + common >= n ? -1 : 1;

        return str[a + common] < str[b + common] ? -1 : (str[a + common] == str[b + common] ? 0 : 1);
    }
};
