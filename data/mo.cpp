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

// solution to https://codeforces.com/problemset/problem/86/D
// source : https://codeforces.com/contest/86/submission/46163034

using mo_value = int;
using mo_answer = int64_t; 

// TODO:
struct mo_state {
    static const int A_MAX = 1e6 + 5;
 
    vector<int> freq;
    int64_t sum;
 
    // TODO:
    mo_state() {
        freq.assign(A_MAX, 0);
        sum = 0;
    }
 
    // TODO:
    void add_left(const mo_value &x) {
        sum += int64_t(2 * freq[x] + 1) * x;
        freq[x]++;
    }
 
    void add_right(const mo_value &x) {
        add_left(x);
    }
 
    // TODO:
    void remove_left(const mo_value &x) {
        freq[x]--;
        sum -= int64_t(2 * freq[x] + 1) * x;
    }
 
    void remove_right(const mo_value &x) {
        remove_left(x);
    }
 
    mo_answer get_answer() const {
        return sum;
    }
};
 
struct mo_query {
    int start, end, block, index;
    mo_answer answer;
 
    mo_query(int _start = 0, int _end = 0) : start(_start), end(_end) {}
 
    bool operator<(const mo_query &other) const {
        if (block != other.block)
            return block < other.block;
 
        return block % 2 == 0 ? end < other.end : other.end < end;
    }
};
 
struct mo {
    int n, block_size;
    vector<mo_value> values;
 
    mo(vector<mo_value> initial = {}) {
        if (!initial.empty())
            init(initial);
    }
 
    void init(const vector<mo_value> &initial) {
        values = initial;
        n = values.size();
        block_size = sqrt(n) + 1;
    }
 
    void update_state(mo_state &state, const mo_query &first, const mo_query &second) const {
        int intersect_start = max(first.start, second.start);
        int intersect_end = min(first.end, second.end);
 
        if (intersect_start >= intersect_end) {
            for (int i = first.start; i < first.end; i++)
                state.remove_left(values[i]);
 
            for (int i = second.start; i < second.end; i++)
                state.add_right(values[i]);
 
            return;
        }
 
        for (int i = first.start; i < intersect_start; i++)
            state.remove_left(values[i]);
 
        for (int i = first.end - 1; i >= intersect_end; i--)
            state.remove_right(values[i]);
 
        for (int i = intersect_start - 1; i >= second.start; i--)
            state.add_left(values[i]);
 
        for (int i = intersect_end; i < second.end; i++)
            state.add_right(values[i]);
    }
 
    vector<mo_answer> solve(vector<mo_query> queries) const {
        for (int i = 0; i < (int) queries.size(); i++) {
            queries[i].index = i;
            queries[i].block = queries[i].start / block_size;
        }
 
        sort(queries.begin(), queries.end());
        mo_state state;
        mo_query last_query;
        vector<mo_answer> answers(queries.size());
 
        for (mo_query &q : queries) {
            update_state(state, last_query, q);
            answers[q.index] = state.get_answer();
            last_query = q;
        }
 
        return answers;
    }
};

int main() {
    ios::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(0);
#endif

    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);

    for (int& a : A)
        cin >> a;

    mo M(A);
    vector<mo_query> queries(Q);

    for (auto& query : queries) {
        cin >> query.start >> query.end;
        --query.start;
    }

    vector<mo_answer> answers = M.solve(queries);

    for (mo_answer ans : answers)
        cout << ans << '\n';
}