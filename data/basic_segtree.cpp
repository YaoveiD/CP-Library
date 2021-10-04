// source : https://github.com/nealwu/competitive-programming/blob/master/seg_tree/basic_seg_tree.cc
// verification : https://atcoder.jp/contests/practice2/submissions/26352976

// TODO: segment_change can be eliminated entirely in favor of just updating with a new segment instead.
struct segment_change {
    // Use a sentinel value rather than a boolean to save significant memory (4-8 bytes per object).
    static const int SENTINEL = ;

    // TODO: check if these values can overflow int.
    int to_set, to_add;

    // TODO: make sure the default constructor is the identity segment_change.
    segment_change(int _to_add = 0, int _to_set = SENTINEL) : to_set(_to_set), to_add(_to_add) {}

    bool has_set() const {
        return to_set != SENTINEL;
    }
};

struct segment {
    // TODO: check if these values can overflow int.
    int maximum;

    // TODO: make sure the default constructor is the identity segment.
    segment() {}

    bool empty() const {
        return ;
    }

    void apply(const segment_change &change) {
        if (change.has_set()) {
            maximum = change.to_set;
        }

        maximum += change.to_add;
    }

    void join(const segment &other) {
        if (empty()) {
            *this = other;
            return;
        } else if (other.empty()) {
            return;
        }

        // TODO
    }

    // TODO: decide whether to re-implement this for better performance. Mainly relevant when segments contain arrays.
    void join(const segment &a, const segment &b) {
        *this = a;
        join(b);
    }
};

int right_half[32];

struct basic_seg_tree {
    // TODO: POWER_OF_TWO_MODE is necessary in order to call query_full() or to binary search the tree.
    static const bool POWER_OF_TWO_MODE = true;

    int tree_n = 0;
    vector<segment> tree;

    basic_seg_tree(int n = -1) {
        if (n >= 0)
            init(n);
    }

    void init(int n) {
        if (POWER_OF_TWO_MODE) {
            tree_n = 1;

            while (tree_n < n)
                tree_n *= 2;
        } else {
            tree_n = n;
        }

        tree.assign(2 * tree_n, segment());
    }

    // Builds our tree from an array in O(n).
    void build(const vector<segment> &initial) {
        int n = int(initial.size());
        init(n);
        assert(n <= tree_n);

        for (int i = 0; i < n; i++)
            tree[tree_n + i] = initial[i];

        for (int position = tree_n - 1; position > 0; position--)
            tree[position].join(tree[2 * position], tree[2 * position + 1]);
    }

    // [a, b]
    segment query(int a, int b) const {
        assert(0 <= a && a <= b && b < tree_n);
        segment answer;
        int r_size = 0;

        for (a += tree_n, b += tree_n + 1; a < b; a /= 2, b /= 2) {
            if (a & 1)
                answer.join(tree[a++]);

            if (b & 1)
                right_half[r_size++] = --b;
        }

        for (int i = r_size - 1; i >= 0; i--)
            answer.join(tree[right_half[i]]);

        return answer;
    }

    segment query_full() const {
        assert(POWER_OF_TWO_MODE);
        return tree[1];
    }

    segment query(int index) const {
        assert(0 <= index && index < tree_n);
        return tree[tree_n + index];
    }

    void join_up(int position) {
        while (position > 1) {
            position /= 2;
            tree[position].join(tree[2 * position], tree[2 * position + 1]);
        }
    }

    void update(int index, const segment_change &change) {
        assert(0 <= index && index < tree_n);
        int position = tree_n + index;
        tree[position].apply(change);
        join_up(position);
    }

    void update(int index, const segment &seg) {
        assert(0 <= index && index < tree_n);
        int position = tree_n + index;
        tree[position] = seg;
        join_up(position);
    }

    int find_first_knowingly(int i, int from, int to, int L, int R, const function<bool(const segment&)>& func) {
        if (!func(tree[i])) {
            return -1;
        }

        if (from > R or to < L) {
            return -1;
        }

        if (from == to) {
            return from;
        }

        int mid = (from + to) / 2;
        int index = find_first_knowingly(i * 2, from, mid, L, R, func);
        if (index == -1) {
            index = find_first_knowingly(i * 2 + 1, mid + 1, to, L, R, func);
        }

        return index;
    }

    // assuming func is non-decreasing.
    // find first index in [L, R] that func(initial[index]) returns true.
    // Note: returns -1 if no such index
    template<typename func_t>
    int find_first(int L, int R, const func_t& func) {
        return find_first_knowingly(1, 0, tree_n - 1, L, R, func);
    }

    template<typename func_t>
    int find_first(const func_t& func) {
        return find_first_knowingly(1, 0, tree_n - 1, 0, tree_n - 1, func);
    }

    template<typename func_t>
    int find_last_knowingly(int i, int from, int to, int L, int R, const func_t& func) {
        if (!func(tree[i])) {
            return -1;
        }

        if (from > R or to < L) {
            return -1;
        }

        if (from == to) {
            return from;
        }

        int mid = (from + to) / 2;
        int index = find_first_knowingly(i * 2 + 1, mid + 1, to, L, R, func);
        if (index == -1) {
            index = find_first_knowingly(i * 2, from, mid, L, R, func);
        }

        return index;
    }

    // havn't verified. I don't know if it works?
    // assuming func is non-increasing.
    // find last index in [L, R] that func(initial[index]) returns true.
    // Note: returns -1 if no such index
    template<typename func_t>
    int find_last(int L, int R, const func_t& func) {
        return find_last_knowingly(1, 0, tree_n - 1, L, R, func);
    }

    template<typename func_t>
    int find_last(const func_t& func) {
        return find_last_knowingly(1, 0, tree_n - 1, 0, tree_n - 1, func);
    }
};