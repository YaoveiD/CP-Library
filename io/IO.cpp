
namespace IO {
  //write
  template<typename T>
  inline void _wr(const T& x) { cout << x; }
  template<typename T, typename U>
  inline void _wr(const pair<T, U>& p) { _wr(p.first); cout << ' '; _wr(p.second); }
  template<typename T>
  inline void _wr(const vector<T>& v) {
    bool first = true;
    for (auto& x : v) {
      if (!first) { cout << ' '; }
      _wr(x);
      first = false;
    }
  }
  template<typename T, typename... U>
  inline void _wr(const T& t, const U&... u) {
    _wr(t);
    cout << ' ';
    _wr(u...);
  }
  inline void wr() { cout << '\n'; }
  template<typename ...T>
  inline void wr(const T&... t) {
    _wr(t...);
    wr();
  }
  // write c stytle array
  #define wv(arr, n) for (int i = 0; i < n; ++i) { if (i > 0) cout << ' '; _wr(arr[i]); } cout << '\n';
  
  //read
  template<typename T>
  inline void re(T& x) { cin >> x; }
  template<typename T, typename... U>
  void re(T&, U&...);
  template<typename T, typename U>
  inline void re(pair<T, U>& p) {
    re(p.first, p.second);
  }
  template<typename T>
  inline void re(vector<T>& v) {
    for (auto& x : v) { re(x); }
  }
  template<typename T, typename... U>
  inline void re(T& t, U&... u) { re(t); re(u...); }
  #define ints(...) int __VA_ARGS__; re(__VA_ARGS__);
  // for c style array, but seldom use I think
  #define rv(arr, n) for (int i = 0; i < n; ++i) { re(arr[i]); }
}
using namespace IO;
