/*
*  author: yaoveil
*  date:   2021-06-22 23:19:24
*/
#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

using namespace std;

const char MIN_CHAR = 'a';
const char MAX_CHAR = 'z';
const int ALPHABET = 26;

template<class T>
class StringGen {
public:
  string itostr(T x) {
    string res;
    while (x) {
      int m = x % ALPHABET;
      res += (m == 0 ? MAX_CHAR : MIN_CHAR + m - 1);
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
      res = res * ALPHABET + s[i] - MIN_CHAR + 1;
    }
    return res;
  }

  void add(string& s) {
    int inc = 1;
    for (int i = (int)s.size() - 1; i >= 0 && inc; --i) {
      if (s[i] + inc > MAX_CHAR) {
        s[i] = MIN_CHAR;
      }
      else {
        s[i]++;
        inc = 0;
      }
    }
    if (inc) {
      s = MIN_CHAR + s;
    }
  }

  void gen(vector<string>& strings, int sz, string start = string(1, MIN_CHAR)) {
    for (int i = 0; i < sz; ++i) {
      strings.push_back(start);
      add(start);
    }
  }
};
