#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <vector>
 
using namespace std;

// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
template<class Fun> class y_combinator_result {
    Fun fun_;
public:
    template<class T> explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
    template<class ...Args> decltype(auto) operator()(Args &&...args) { return fun_(std::ref(*this), std::forward<Args>(args)...); }
};
template<class Fun> decltype(auto) y_combinator(Fun &&fun) { return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun)); }

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '['; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << ']'; }
 
void debug_out() { cerr << endl; }
template<typename Head, typename... Tail> void debug_out(Head H, Tail... T) { cerr << ' ' << H; debug_out(T...); }
#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 
#endif

// I mean, useless algorithm
// all of these start with 0

const int N_MAX = 21;
int64_t facts[N_MAX] = {1};

// returns the 0-started order of a permutation in O(n^2) time.
// can be optimized to O(nlogn) by fenwick tree if needed.
int64_t cantor(const vector<int>& permutation) {
    int n = int(permutation.size());
    int64_t encoding = 0;
    vector<int> suffix_less_count(n);

    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (permutation[i] > permutation[j])
                suffix_less_count[i]++;

    for (int i = 0; i < n; ++i)
        encoding += suffix_less_count[i] * facts[n - i - 1];

    return encoding;
}

// returns a n-permutation whose order is order(0-started).
// can be optimized by bst
vector<int> decantor(int64_t order, int n) {
    vector<int> suffix_less_count(n);

    for (int i = 0; i < n; ++i) {
        suffix_less_count[i] = order / facts[n - i - 1];
        order -= facts[n - i - 1] * suffix_less_count[i];
    }

    vector<int> rest(n);
    iota(rest.begin(), rest.end(), 0);
    vector<int> perm(n);

    for (int i = 0; i < n; ++i) {
        perm[i] = rest[suffix_less_count[i]];
        rest.erase(lower_bound(rest.begin(), rest.end(), perm[i]));
    }

    return perm;
}

void prepare_facts() {
    for (int i = 1; i < N_MAX; ++i)
        facts[i] = facts[i - 1] * i;
}

int main() {
    prepare_facts();

    vector<int> perm(4);
    iota(perm.begin(), perm.end(), 0);

    do {
        debug(perm, cantor(perm));
        int c = cantor(perm);
        assert(decantor(c, 4) == perm);
    } while (next_permutation(perm.begin(), perm.end()));
}