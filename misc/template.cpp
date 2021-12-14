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

typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<int64_t> vl;

#define FOR(i, a, b) for (int i=a; i<(b); ++i)
#define F0R(i, a) for (int i=0; i<(a); ++i)
#define each(i, C) for (auto &i : C)
#define sz(x) int((x).size())
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define ins insert
 
vi range(int n, int start = 0) { vi r(n); iota(all(r), start); return r; }
template<class T> bool setmin(T& a, T b) { return b < a ? a = b, true : false; }
template<class T> bool setmax(T& a, T b) { return a < b ? a = b, true : false; }

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '['; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << ']'; }

void debug_out() { cerr << endl; }
template<typename Head, typename... Tail> void debug_out(Head H, Tail... T) { cerr << ' ' << H; debug_out(T...); }
#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...)
#endif
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tests; cin >> tests; while (tests--) run_case();
}