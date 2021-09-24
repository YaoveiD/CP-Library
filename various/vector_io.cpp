#include <bits/stdc++.h>

using namespace std;

template<typename T, typename U>
istream& operator>>(istream& is, pair<T, U>& p) {
  is >> p.first >> p.second;
  return is;
}
template<typename T>
istream& operator>>(istream& is, vector<T>& v) {
  for (auto& i : v) is >> i;
  return is;
}

template<typename T, typename U>
pair<T, U>& operator--(pair<T, U>& p) {
  --p.first; --p.second;
  return p;
}
template<typename T>
vector<T>& operator--(vector<T> &v){
  for (auto& i : v) --i;
  return  v;
}
template<typename T, typename U>
pair<T, U>& operator++(pair<T, U>& p) {
  ++p.first; ++p.second;
  return p;
}
template<typename T>
vector<T>& operator++(vector<T> &v){
  for (auto& i : v) ++i;
  return  v;
}

template<typename T, typename U>
ostream& operator<<(ostream& os, const pair<T, U>& p) {
  os << p.first << ' ' << p.second;
  return os;
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

template<typename T, typename U, typename V>
pair<T, U> operator+(const pair<T, U>& p, V add) {
  return pair<T, U>{p.first + add, p.second + add};
}
template<typename T, char sep = ' '>
void vout(const vector<T>& v, int add = 0, int start = -1, int end = -1) {
  if (start < 0) start = 0;
  if (end < 0) end = (int) v.size();

  for (int i = start; i < end; ++i) {
    if (i != start) {
      cout << sep;
    }
    cout << v[i] + add;
  }
  cout << '\n';
}

int main() {
  vector<pair<int, int>> A(2);
  cin >> A;
  auto B = ++A; --A;
  cout << A << '\n';
  cout << B << '\n';
  vector<int> C(3);
  vout(A, 1);
  vout(A, -2);
  return 0;
}