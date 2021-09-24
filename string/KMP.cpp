#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>

using namespace std;

typedef unsigned long long hash_t;

#define FOR(i, N) for(int i=0; i<N; ++i) 

const int MX = 100001;
const int base = 133;

class KMP {
public:
  vector<int> next;

  void get_next(const string& S) {
    int N = (int) S.size();
    next.resize(N);
    int cur = 0, i = 1;
    next[0] = 0;
    while (i < N) {
      if (S[cur] == S[i]) {
        next[i++] = ++cur;
      } else if (cur != 0) {
        cur = next[cur - 1];
      } else {
        next[i++] = 0;
      }
    }
  }

  int kmp(const string& S, const string& T) {
    int ret = 0;
    int N = (int) S.size(), M = (int) T.size();
    int i = 0, j = 0;
    get_next(T);
    while (i < N) {
      if (S[i] == T[j]) {
        ++i; ++j;
      } else if (j != 0) {
        j = next[j - 1];
      } else {
        ++i;
      }
      if (j == M) {
        ++ret;
        j = next[j - 1];
      }
    }
    return ret;
  }

};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  KMP kmper;
  while (tt--) {
    string S, T;
    cin >> T >> S;
    cout << kmper.kmp(S, T) << '\n';
  }
  return 0;
}
