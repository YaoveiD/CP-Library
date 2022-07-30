#include <bits/stdc++.h>
using namespace std;

auto random_address = [] { char *p = new char; delete p; return uint64_t(p); };
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1));
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1));

template<typename integer_t>
inline integer_t rand(integer_t from, integer_t to) {
  return uniform_int_distribution<integer_t>(from, to)(rng);
}

template<>
inline int64_t rand(int64_t from, int64_t to) {
  return uniform_int_distribution<int64_t>(from, to)(rng64);
}

template<>
inline double rand(double from, double to) {
  return uniform_real_distribution<double>(from, to)(rng);
}

inline namespace generator {
  string gen_string(int len, int CAP = 0, int from = 1, int to = 26) {
    assert(len >= 0);
    string str(len, (CAP ? 'A' : 'a'));
    for (char &ch : str)
      ch += rand(from, to) - 1;
    return str;
  }

  string gen_string(int len, const string &base) {
    assert(len >= 0);
    string str;
    int n = int(base.size());
    str.reserve(len);
    for (int i = 0; i < len; ++i)
      str.push_back(base[rand(0, n - 1)]);
    return str;
  }
  
  vector<int> gen_perm(int len, int start = 1) {
    assert(len >= 0);
    vector<int> perm(len);
    iota(perm.begin(), perm.end(), start);
    shuffle(perm.begin() , perm.end() , rng);
    return perm;
  }

  template<typename T>
  vector<T> gen_array(int len, T from = 0, T to = numeric_limits<T>::max()){
    assert(len >= 0);
    vector<T> arr(len);
    for (auto &x : arr)
      x = rand(from, to);
    return arr;
  }

  /* Returns `size` unordered (unsorted) distinct numbers between `from` and `to`. */
  template<typename T>
  vector<T> gen_distinct(int size, T from = 0, T to = numeric_limits<T>::max()) {
    vector<T> result;

    if (size == 0)
      return result;

    assert(from <= to && size >= 0);
    int64_t n = to - from + 1;
    assert(size <= n);
    double expected = 0.0;

    for (int i = 1; i <= size; i++)
      expected += double(n) / double(n - i + 1);
    
    if (expected < double(n)) {
      set<T> vals;
        
      while (int(vals.size()) < size) {
        T x = rand(from, to);

        if (vals.insert(x).second)
          result.push_back(x);
      }
    } else {
      assert(n <= 1000000000);
      vector<int> p = gen_perm(int(n), from);
      result.insert(result.end(), p.begin(), p.begin() + size);
    }

    return result;
  }

  /* Returns random (unsorted) partition which is a representation of sum as a sum of integers not less than min_part. */
  template<typename T>
  vector<T> gen_partition(int size, T sum, T min_part) {
    assert(size >= 0);
    assert(size != 0 || sum == 0);
    assert(min_part * size <= sum); 

    if (size == 0 && sum == 0)
          return vector<T>();

    T sum_ = sum;
    sum -= min_part * size;

    vector<T> septums(size);
    vector<T> d = gen_distinct(size - 1, T(1), T(sum + size - 1));
    for (int i = 0; i + 1 < size; i++)
      septums[i + 1] = d[i];
    sort(septums.begin(), septums.end());

    vector<T> result(size);
    for (int i = 0; i + 1 < size; i++)
      result[i] = septums[i + 1] - septums[i] - 1;
    result[size - 1] = sum + size - 1 - septums.back();

    for (size_t i = 0; i < result.size(); i++)
      result[i] += min_part;
    
    T result_sum = 0;
    for (size_t i = 0; i < result.size(); i++)
      result_sum += result[i];

    if (result_sum != sum_) {
      cerr << "random_t::partition: partition sum is expected to be the given sum" << endl;
      exit(0);
    }
    if (*min_element(result.begin(), result.end()) < min_part) {
      cerr << "random_t::partition: partition min is expected to be no less than the given min_part" << endl;
      exit(0);
    }
    if (int(result.size()) != size || result.size() != (size_t) size) {
      cerr << "random_t::partition: partition size is expected to be equal to the given size" << endl;
      exit(0);
    }

    return result;
  }

  /* Returns random (unsorted) partition which is a representation of sum as a sum of positive integers. */
  template<typename T>
  vector<T> gen_partition(int size, T sum) {
    return gen_partition(size, sum, T(1));
  }

  vector<pair<int, int>> gen_tree(int n){
    assert(n >= 0);
    static const int P_SIZE = 1000005;
    static int permutation[P_SIZE];
    vector<pair<int, int>> res(n ? n - 1 : 0);
    iota(permutation, permutation + 1 + n, 0);
    shuffle(permutation + 1, permutation + 1 + n, rng);
    
    for(int i = 2; i <= n; ++i){
      int u = i, v = rand(1 , i - 1);
      u = permutation[u], v = permutation[v];
      res[i - 2] = minmax(u, v); // u < v, just for convenience while debugging
    }
    
    shuffle(res.begin() , res.end() , rng);
    return res;
  }

  vector<pair<int, int>> gen_simple_graph(int n, int m) {
    assert(n > 0 && m >= n);
    int max_edges = n * (n - 1) / 2;
    assert(m <= max_edges);
    vector<pair<int, int>> res = gen_tree(n);
    set<pair<int, int>> edge(res.begin(), res.end());
    
    for (int i = n; i <= m; ++i)
      while (true) {
        int u = rand(1, n), v = rand(1, n);
        
        if (u == v)
          continue;
        
        auto it = edge.insert(minmax(u, v));
        
        if (it.second)
          break;
      }
    
    res.assign(edge.begin(), edge.end());
    return res;
  }
}

template<typename T, typename U>
ostream& operator<<(ostream &os, const pair<T, U> &p) {
  os << p.first << ' ' << p.second;
  return os;
}

template<typename T>
ostream& operator<<(ostream &os, const vector<T> &v) {
  for (size_t i = 0, n = v.size(); i < n; ++i) {
    os << v[i];

    if (i != n - 1)
      os << ' ';
  }
  
  return os;
}

// a special case
template<typename T, typename U>
ostream& operator<<(ostream &os, const vector<pair<T, U>> &v) {
  for (size_t i = 0, n = v.size(); i < n; ++i)
    os << v[i] << '\n';
  
  return os;
}

const int N_MAX = 50;

// complete this function according to the requirements
void generate_test() {
}

int main() {
  int tests = 1;
  // static const int TESTS_MAX = 10;
  // tests = rand(1, TESTS_MAX); cout << tests << '\n';

  while (tests--)
    generate_test();
}
