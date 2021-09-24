
// sync_with_stdio
// string and char* perform worse
namespace IO {
  //write
  template<typename T>
  inline void wone(T x) { if (x > 9) wone(x / 10); putchar(x % 10 + 48); }
  template<typename T>
  inline void wr(char sep, T x) { if(x < 0) putchar('-'), x = -x; wone(x); }
  inline void wr(char sep, const char* x) { printf("%s", x); }
  inline void wr(char sep, double x) { printf("%f", x); }
  inline void wr(char sep, const string& x) { cout << x; }
  template<typename T, typename U>
  inline void wr(char sep, const pair<T, U>& p) { wr(sep, p.first); putchar(' '); wr(sep, p.second); }
  template<typename T>
  inline void wr(char sep, const vector<T>& v) {
    bool first = true;
    for (auto& x : v) {
      if (!first) { putchar(' '); }
      wr(sep, x);
      first = false;
    }
  }
  template<typename T, typename... U>
  void wr(char sep, const T& t, const U&... u) {
    wr(sep, t);
    putchar(sep);
    wr(sep, u...);
  }
  void write() { putchar('\n'); }
  template<typename ...T>
  void write(const T&... t) {
    wr(' ', t...);
    write();
  }

  //read
  template<typename T>
  inline void read(T& x) {
    x = 0; T f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -1;
    for (; isdigit(c); c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
    x *= f;
  }
  inline void read(char* x) { scanf("%s", x); }
  inline void read(double& x) { scanf("%lf", &x); }
  inline void read(string& x) { cin >> x; }
  template<typename T, typename... U>
  void read(T&, U&...);
  template<typename T, typename U>
  inline void read(pair<T, U>& p) {
    read(p.first, p.second);
  }
  template<typename T>
  inline void read(vector<T>& v) {
    for (auto& x : v) { read(x); }
  }
  template<typename T, typename... U>
  void read(T& t, U&... u) { read(t); read(u...); }
  #define ints(...) int __VA_ARGS__; read(__VA_ARGS__);
  // for c style array, but seldom use I think
  #define rv(arr, n) for (int i = 0; i < n; ++i) { read(arr[i]); }
  #define pv(arr, n) { for (int i = 0; i < n; ++i) { if (i > 0) putchar(' '); wr(' ', arr[i]); } putchar('\n'); }  
}
using namespace IO;