#include <bits/stdc++.h>
using namespace std;

#define sz(c) int(c.size())
#define all(c) c.begin(), c.end()

auto random_address = [] { char *p = new char; delete p; return uint64_t(p); };
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1));

// P = 2^32 - 13337 is a safe prime: both P and (P - 1) / 2 are prime.
extern const unsigned HASH_P = unsigned(-13337);
using hash_t = uint64_t;

// Avoid multiplication bases near 0 or P - 1.
uniform_int_distribution<unsigned> MULT_DIST(unsigned(0.1 * HASH_P), unsigned(0.9 * HASH_P));
const unsigned HASH_MUL = MULT_DIST(rng);

template<unsigned mod = HASH_P>
struct string_hash {
    static const bool BUILD_REVERSE = true;
    static vector<hash_t> pows;

    vector<hash_t> prefix_hash;
    vector<hash_t> suffix_hash;

    string_hash() {}

    string_hash(const string &str) {
        build(str);
    }

    void build(const string &str) {
        int n = int(str.size());
        prefix_hash.assign(n + 1, 0);

        // Note: we add `1` to fix strings that start with 0.
        for (int i = 0; i < n; ++i)
            prefix_hash[i + 1] = (prefix_hash[i] * HASH_MUL + str[i] + 1) % mod;

        if (BUILD_REVERSE) {
            suffix_hash.assign(n + 1, 0);
            
            for (int i = n - 1; i >= 0; --i)
                suffix_hash[i] = (suffix_hash[i + 1] * HASH_MUL + str[i] + 1) % mod;
        }

        while (int(pows.size()) <= n)
            pows.push_back(pows.back() * HASH_MUL % mod);
    }

    int length() const {
        return int(prefix_hash.size()) - 1;
    }

    hash_t complete_hash() const {
        return prefix_hash.back();
    }

    hash_t sub_hash(int start, int end) const {
        assert(0 <= start && start <= end && end <= length());
        hash_t value = prefix_hash[end] + mod - prefix_hash[start] * pows[end - start] % mod;
        return value >= mod ? value - mod : value;
    }

    hash_t rev_sub_hash(int start, int end) const {
        assert(BUILD_REVERSE && 0 <= start && start <= end && end <= length());
        hash_t value = suffix_hash[start] + mod - suffix_hash[end] * pows[end - start] % mod;
        return value >= mod ? value - mod : value;
    }

    bool equal(int start1, int start2, int len) const {
        return sub_hash(start1, start1 + len) == sub_hash(start2, start2 + len);
    }

    bool is_palindrome(int start, int end) const {
        return sub_hash(start, end) == rev_sub_hash(start, end);
    }
};

template<unsigned mod>
vector<hash_t> string_hash<mod>::pows = {1};
