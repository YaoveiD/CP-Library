#include <bits/stdc++.h>

#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#pragma GCC optimize("unroll-loops")
 
using namespace std;

//typedef
typedef long long LL;
 
typedef pair<int, int> pii;
typedef pair<LL,LL> pll;
typedef pair<double, double> pdd;
typedef tuple<int, int, int> tiii;

typedef vector<int> vi;
typedef vector<double> vd;
typedef vector<LL> vll;
typedef vector<pii> vpii;
typedef vector<pdd> vpdd;
typedef vector<pll> vpll;
typedef vector<tiii> vtiii;

//templates
template<class T> using pq = priority_queue<T>;
template<class T> using pqg = priority_queue<T, vector<T>, greater<T>>;
template<class T> inline bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> inline bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
template<typename T, typename U>
istream& operator>>(istream& is, pair<T, U>& p) {
  is >> p.first >> p.second;
  return is;
}
template<typename T, typename U>
ostream& operator<<(ostream& os, const pair<T, U>& p) {
  os << p.first << ' ' << p.second;
  return os;
}
template<typename T>
istream& operator>>(istream& is, vector<T>& v) {
  for (auto& i : v) is >> i;
  return is;
}
template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
  int f = 0;
  for (auto& i : v) {
    if (f++) os << ' ';
    os << i;
  }
  return os;
}
template<typename T>
vector<T>& operator--(vector<T> &v){
  for (auto& i : v) --i;
  return  v;
}
template<typename T>
vector<T>& operator++(vector<T> &v){
  for (auto& i : v) ++i;
  return  v;
}
template <typename T, typename Iter>
int find_position(Iter b, Iter e, const T& x) {
  auto it = lower_bound(b, e, x);
  if (it != e && *it == x) {
    return it - b;
  } else {
    return -1;
  }
}
template<typename T>
inline T median(T a,T b,T c) {
  return 1LL*(a + b + c) - max({a, b, c}) - min({a, b, c});
}
template<typename T>
inline long long max(const T& v) {
  return *max_element(v.begin(), v.end());
}
template<typename T>
inline long long min(const T& v) {
  return *min_element(v.begin(), v.end());
}
template<typename T>
inline long long sum(const T& v) {
  return accumulate(v.begin(), v.end(), 0LL);
}

//seldom use source https://codeforces.com/contest/1545/submission/122090297 Benq
constexpr int pct(int x) {
  return __builtin_popcount(x);
} // # of bits set
constexpr int bits(int x) {
  return x == 0 ? 0 : 31-__builtin_clz(x);
} // floor(log2(x)) 
int64_t cdiv(int64_t a, int64_t b) {
  return a/b + ((a^b)>0 && a%b);
} // divide a by b rounded up
int64_t fdiv(int64_t a, int64_t b) {
  return a/b - ((a^b)<0 && a%b);
} // divide a by b rounded down

//macro
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define UID(L, R) uniform_int_distribution<int>(L, R)(rng)

#define REP(I, A, B) for (int I = (A); I < (B); ++I)
#define FOR(I, N) REP(I, 0, N)
#define each(E, V) for (auto& E : V)

#define ALL(X) (X).begin(), (X).end()
#define RALL(X) (X).rbegin(), (X).rend()
#define UNIQUE_SORT(V) (sort(ALL(V)), V.resize(distance(V.begin(), unique(ALL(V)))))
#define SZ(X) (int)(X).size()
#define LB lower_bound
#define UB upper_bound
#define MP make_pair

//constexpr
const int SIZE = 1 << 19;
const LL infll = (LL) 1e18;
const int inf = 0x3f3f3f3f;

// make sure to intialize all global vars
// uncomment cin >> tt? 
void solve() {
  
}
 
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int tt = 1;
  //cin >> tt;
  while (tt--) {
    solve();
  }

  return 0;
}
