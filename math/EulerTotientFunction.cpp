/*
* author:  yaoveil
* created: 2021-08-17 18:03:18
*/

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

vector<bool> prime;
vector<int> primes;
vector<int64_t> phi;

void sieve(int maximum = 100000) {
  maximum = max(maximum, 1);
  prime.assign(maximum + 1, true);
  prime[0] = prime[1] = false;
  primes = {};
  phi[1] = 1;

  for (int p = 2; p <= maximum; ++p) {
    if (prime[p]) {
      primes.push_back(p);
      phi[p] = p - 1;
    }

    for (int j = 0; j < (int) primes.size() and (int64_t) primes[j] * p <= maximum; ++j) {
      prime[primes[j] * p] = false;
      
      if (p % primes[j]) {
        phi[primes[j] * p] = (primes[j] - 1) * phi[p];
      } else {
        phi[primes[j] * p] = primes[j] * phi[p];
        break;
      }
    }
  }
}
 
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  
  return 0;
}
