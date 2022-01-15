#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
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

// BUFFS?
// #pragma GCC optimize("O3")
// #pragma GCC target("sse4")
// #pragma GCC optimize("unroll-loops")

//typedef
typedef int64_t LL;
typedef pair<int, int> pii;
typedef pair<LL,LL> pll;
typedef vector<int> vi;
typedef vector<LL> vll;

//templates
template<class T> using pq = priority_queue<T>;
template<class T> using pqg = priority_queue<T, vector<T>, greater<T>>;
template<class T> inline bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> inline bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
template<typename T, typename U> istream& operator>>(istream& is, pair<T, U>& p) { is >> p.first >> p.second; return is; }
template<typename T, typename U> ostream& operator<<(ostream& os, const pair<T, U>& p) { os << p.first << ' ' << p.second; return os; }
template<typename T> istream& operator>>(istream& is, vector<T>& v) { for (auto& i : v) is >> i; return is; }
template<typename T> ostream& operator<<(ostream& os, const vector<T>& v) { int f = 0; for (auto& i : v) { if (f++) os << ' '; os << i; } return os; }

int64_t cdiv(int64_t a, int64_t b) { return a/b + ((a^b)>0 && a%b); } // divide a by b rounded up
int64_t fdiv(int64_t a, int64_t b) { return a/b - ((a^b)<0 && a%b); } // divide a by b rounded down

//macro
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define UID(L, R) uniform_int_distribution<int>(L, R)(rng)
#define F0R(i, n) for (int i = 0; i < (n); ++i)
#define FOR(i, a, b) for (int i = a; i < (b); ++i)
#define each(i, c) for (auto &i : c)
#define all(c) c.begin(), c.end()
#define sz(c) int(c.size())
