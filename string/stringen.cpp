/*
*  author: yaoveil
*  date:   2021-06-22 23:19:24
*/
template<class T>
class StringGen {
public:
  string itostr(T x) {
    string res;
    while (x) {
      int m = x % 26;
      res += (m == 0 ? 'z' : 'a' + m - 1);
      if (m == 0) {
        --x;
      }
      x /= 26;
    }
    reverse(res.begin(), res.end());
    return res;
  }

  T strtoi(const string& s) {
    T res = 0;
    for (int i = 0; i < (int)s.size(); ++i) {
      res = res * 26 + s[i] - 'a' + 1;
    }
    return res;
  }

  void add(string& s) {
    int inc = 1;
    for (int i = (int)s.size() - 1; i >= 0 && inc; --i) {
      if (s[i] + inc > 'z') {
        s[i] = 'a';
      }
      else {
        s[i]++;
        inc = 0;
      }
    }
    if (inc) {
      s = 'a' + s;
    }
  }

  void gen(vector<string>& strings, int sz, string start = "a") {
    for (int i = 0; i < sz; ++i) {
      strings.push_back(start);
      add(start);
    }
  }
};