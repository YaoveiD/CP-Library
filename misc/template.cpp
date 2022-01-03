#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

typedef int64_t ll;
typedef pair<int, int> pii;
typedef pair<ll,ll> pll; 
typedef vector<int> vi;
typedef vector<ll> vl;

#define F0R(i, n) for (int i = 0; i < n; ++i)
#define FOR(i, a, b) for (int i = a; i < (b); ++i)
#define sz(c) int(c.size())
#define all(c) c.begin(), c.end()

template<class T> inline bool setmin(T& a, T b) { return b < a ? a = b, true : false; }
template<class T> inline bool setmax(T& a, T b) { return a < b ? a = b, true : false; }

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '['; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << ']'; }

void debug_out() { cerr << endl; }
template<typename Head, typename... Tail> void debug_out(Head H, Tail... T) { cerr << ' ' << H; debug_out(T...); }
#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 
#endif

void run_case() {
    
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tests = 1;
    cin >> tests;

    while (tests--)
        run_case();
}