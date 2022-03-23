#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>

using namespace std;

typedef unsigned long long hash_t;

const int base = 133;

// a template for string hash based on unsigned long long
vector<hash_t> pows;

class Hash {
public:
    vector<hash_t> prefix_hash;
    int N;

    Hash(const string &S) {
        build(S);
    }

    void build(const string &S) {
        N = (int) S.size();
        assert(N > 0);
        prefix_hash.assign(N + 1, 0);
        for (int i = 0; i < N; ++i)
            prefix_hash[i + 1] = prefix_hash[i] * base + S[i];
        if (pows.size() == 0)
            pows.push_back(1);
        pows.reserve(N + N/32 + 1);
        while ((int) pows.size() <= N + N/32)
            pows.push_back(pows.back() * base);
    }

    // [from, to)
    hash_t sub_hash(int from, int to) {
        assert(0 <= from && to <= N && from < to);
        return prefix_hash[to] - prefix_hash[from] * pows[to - from];
    }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  string S;
  while (cin >> S and S != ".") {
    int N = (int) S.size();
    int ans = 1;
    Hash hasher(S);
    for (int k = 1; k <= N; ++k) if (N % k == 0) {
      bool failed = false;
      const hash_t val = hasher.sub_hash(0, k);
      for (int i = 0; i < N; i += k) {
        if (hasher.sub_hash(i, i + k) != val) {
          failed = true;
          break;
        }
      }
      if (!failed) {
        ans = N / k;
        break;
      }
    }
    cout << ans << '\n';
  }

  return 0;
}
