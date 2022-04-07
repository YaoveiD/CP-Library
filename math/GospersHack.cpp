// generate k-subset mask of n element starting from (1 << k) - 1
struct GospersHack {
    int n, k;
    int p2;
    int current;

    GospersHack(int _n, int _k) : n(_n), k(_k) {
        current = (1 << k) - 1;
        p2 = (1 << n);
    }

    int next_mask() {
        if (current >= p2)
            return -1;

        int ret = current;
        int lowbit = current & -current;
        int r = current + lowbit;
        current = ((r ^ current) >> (__builtin_ctz(lowbit) + 2)) | r;
        
        return ret;
    }
};
