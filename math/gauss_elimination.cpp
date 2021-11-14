#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
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

// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
template<class Fun> class y_combinator_result {
    Fun fun_;
public:
    template<class T> explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
    template<class ...Args> decltype(auto) operator()(Args &&...args) { return fun_(std::ref(*this), std::forward<Args>(args)...); }
};
template<class Fun> decltype(auto) y_combinator(Fun &&fun) { return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun)); }

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '['; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << ']'; }
 
void debug_out() { cerr << endl; }
template<typename Head, typename... Tail> void debug_out(Head H, Tail... T) { cerr << ' ' << H; debug_out(T...); }
#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 
#endif

const double EPS = 1e-9;

// solution to https://www.luogu.com.cn/problem/P3389
// Note: the size of A is N*N
// sum(A(row, i) * x_i) = B_row
// returns X: the solution of equation
// Note: returns a empty vector if there are multiple solutions.

vector<double> gauss(vector<vector<double>> A, const vector<double>& B) {
    int R = int(A.size()), C = int(A[0].size());
    assert(R == C && B.size() == A.size());

    for (int r = 0; r < R; ++r)
        A[r].push_back(B[r]);

    for (int i = 0; i < C; ++i) {
        int max_row = i;

        for (int r = i + 1; r < R; ++r)
            if (fabs(A[r][i]) > fabs(A[max_row][i]))
                max_row = r;

        for (int c = i; c <= C; ++c)
            swap(A[i][c], A[max_row][c]);

        // multiple solutions
        if (fabs(A[i][i]) < EPS)
            return vector<double>();

        for (int r = 0; r < R; ++r)
            if (r != i && fabs(A[r][i]) > EPS) {
                double t = A[r][i] / A[i][i];

                for (int c = i; c <= C; ++c)
                    A[r][c] -= A[i][c] * t;
            }
    }

    vector<double> ans(C);
    
    for (int r = 0; r < R; ++r)
        ans[r] = A[r][C] / A[r][r];

    return ans;
}

// source : https://github.com/ShahjalalShohag/code-library/blob/master/Math/GaussianElimination.cpp
int Gauss(vector<vector<double>> a, vector<double> &ans) {
  int n = (int)a.size(), m = (int)a[0].size() - 1;
  vector<int> pos(m, -1);
  double det = 1; int rank = 0;
  for(int col = 0, row = 0; col < m && row < n; ++col) {
    int mx = row;
    for(int i = row; i < n; i++) if(fabs(a[i][col]) > fabs(a[mx][col])) mx = i;
    if(fabs(a[mx][col]) < EPS) {det = 0; continue;}
    for(int i = col; i <= m; i++) swap(a[row][i], a[mx][i]);
    if (row != mx) det = -det;
    det *= a[row][col];
    pos[col] = row;
    for(int i = 0; i < n; i++) {
      if(i != row && fabs(a[i][col]) > EPS) {
        double c = a[i][col] / a[row][col];
        for(int j = col; j <= m; j++) a[i][j] -= a[row][j] * c;
      }
    }
    ++row; ++rank;
  }
  ans.assign(m, 0);
  for(int i = 0; i < m; i++) {
    if(pos[i] != -1) ans[i] = a[pos[i]][m] / a[pos[i]][i];
  }
  for(int i = 0; i < n; i++) {
    double sum = 0;
    for(int j = 0; j < m; j++) sum += ans[j] * a[i][j];
    if(fabs(sum - a[i][m]) > EPS) return -1; //no solution
  }
  for(int i = 0; i < m; i++) if(pos[i] == -1) return 2; //infinte solutions
  return 1; //unique solution
}

int main() {
    ios::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(0);
#endif
    cout << fixed << setprecision(2);

    int N;
    cin >> N;
    vector<vector<double>> A(N, vector<double>(N));
    vector<double> B(N);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            cin >> A[i][j];

        cin >> B[i];
    }

    vector<double> solution = gauss(A, B);

    if (solution.empty()) {
        cout << "No Solution" << '\n';
    } else {
        for (double x : solution)
            cout << x << '\n';
    }
}