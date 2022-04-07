#include <bits/stdc++.h>
using namespace std;

const int N = 105, MOD = 998244353;

int power(long long n, long long k) {
  int ans = 1 % MOD;
  n %= MOD;
  if (n < 0)
    n += MOD;
  while (k) {
    if (k & 1)
      ans = (long long)ans * n % MOD;
    n = (long long)n * n % MOD;
    k >>= 1;
  }
  return ans;
}

// source : https://github.com/ShahjalalShohag/code-library/blob/master/Math/Determinant%20under%20Prime%20Modulo.cpp
// returns the determinant of a under prime MODular.

int Gauss(vector<vector<int>> a) {
  int n = a.size(), m = (int)a[0].size();
  const long long MODSQ = (long long)MOD * MOD;
  int det = 1, rank = 0;
  for (int col = 0, row = 0; col < m && row < n; col++) {
    int mx = row;
    for (int k = row; k < n; k++)
      if (a[k][col] > a[mx][col])
        mx = k;
    if (a[mx][col] == 0) {
      det = 0;
      continue;
    }
    for (int j = col; j < m; j++)
      swap(a[mx][j], a[row][j]);
    if (row != mx)
      det = det == 0 ? 0 : MOD - det;
    det = 1LL * det * a[row][col] % MOD;
    int inv = power(a[row][col], MOD - 2);
    for (int i = 0; i < n && inv; i++) {
      if (i != row && a[i][col]) {
        int x = ((long long)a[i][col] * inv) % MOD;
        for (int j = col; j < m && x; j++) {
          if (a[row][j])
            a[i][j] = (MODSQ + a[i][j] - ((long long)a[row][j] * x)) % MOD;
        }
      }
    }
    row++;
    ++rank;
  }
  return det;
}

int32_t main() {
  int n;
  cin >> n;
  vector<vector<int>> a(n, vector<int>(n));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      cin >> a[i][j];
  cout << Gauss(a) << '\n';
  return 0;
}