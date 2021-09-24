// https://github.com/nealwu/competitive-programming/tree/master/mod

template<int md>
class _mod_int {
public:
  int val;

  _mod_int(int64_t v = 0) {
    if (v < 0)
      v = v % md + md;
    if (v >= md)
      v %= md;
    val = int(v);
  }

  _mod_int(int v) : _mod_int(int64_t(v)) {}
  _mod_int(unsigned v) : _mod_int(int64_t(v)) {}

  static int inv_mod(int a, int m = md) {
    // https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm#Example
    int g = m, r = a, x = 0, y = 1;

    while (r != 0) {
      int q = g / r;
      g %= r;
      swap(g, r);
      x -= q * y;
      swap(x, y);
    }

    return x < 0 ? x + m : x;
  }

  explicit operator int() const { return val; }
  explicit operator unsigned() const { return val; }
  explicit operator int64_t() const { return val; }

  _mod_int& operator+=(const _mod_int &other) {
    val -= md - other.val;
    if (val < 0)
      val += md;
    return *this;
  }
  _mod_int& operator-=(const _mod_int &other) {
    val -= other.val;
    if (val < 0)
      val += md;
    return *this;
  }
  _mod_int &operator*=(const _mod_int &other) {
    val = int64_t(val) * other.val % md;
    return *this;
  }
  _mod_int &operator/=(const _mod_int &other) { return *this *= other.inv(); }

  friend _mod_int operator+(const _mod_int &a, const _mod_int &b) {
    return _mod_int(a) += b;
  }
  friend _mod_int operator-(const _mod_int &a, const _mod_int &b) {
    return _mod_int(a) -= b;
  }
  friend _mod_int operator*(const _mod_int &a, const _mod_int &b) {
    return _mod_int(a) *= b;
  }
  friend _mod_int operator/(const _mod_int &a, const _mod_int &b) {
    return _mod_int(a) /= b;
  }

  _mod_int& operator++() {
    val = val == md - 1 ? 0 : val + 1;
    return *this;
  }
  _mod_int& operator--() {
    val = val == 0 ? md - 1 : val - 1;
    return *this;
  }

  _mod_int operator-() const { return val == 0 ? 0 : md - val; }

  friend bool operator==(const _mod_int &a, const _mod_int &b) {
    return a.val == b.val;
  }
  friend bool operator!=(const _mod_int &a, const _mod_int &b) {
    return a.val != b.val;
  }
  friend bool operator<(const _mod_int &a, const _mod_int &b) {
    return a.val < b.val;
  }

  _mod_int inv() const { return inv_mod(val); }

  _mod_int pow(int64_t p) const {
    if (p < 0)
      return inv().pow(-p);

    _mod_int a = *this, result = 1;

    while (p > 0) {
      if (p & 1)
        result *= a;

      p >>= 1;

      if (p > 0)
        a *= a;
    }

    return result;
  }

  friend string to_string(const _mod_int& m) {
    return to_string(m.val);
  }

  friend ostream& operator<<(ostream& os, const _mod_int& m) {
    return os << m.val;
  }
};

const int MOD = (int) 1e9 + 7;
using mint = _mod_int<MOD>;
