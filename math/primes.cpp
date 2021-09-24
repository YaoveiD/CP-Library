
// copied from neal's codeforces submission

bool is_prime(int64_t n) {
  if (n < 2)
    return false;

  if (n > 2 && n % 2 == 0)
    return false;

  for (int64_t i = 3; i * i <= n; i += 2)
    if (n % i == 0)
      return false;

  return true;
}

vector<int> smallest_factor;
vector<bool> prime;
vector<int> primes;

// n * log (log n)
void sieve(int maximum) {
  maximum = max(maximum, 1);
  smallest_factor.assign(maximum + 1, 0);
  prime.assign(maximum + 1, true);
  prime[0] = prime[1] = false;
  primes = {};

  for (int p = 2; p <= maximum; p++) {
    if (prime[p]) {
      smallest_factor[p] = p;
      primes.push_back(p);

      for (int64_t i = int64_t(p) * p; i <= maximum; i += p) {
        if (prime[i]) {
          prime[i] = false;
          smallest_factor[i] = p;
        }
      }
    }
  }
}

// O(n)
void linear_sieve(int maximum) {
  prime.assign(maximum + 1, true);
  smallest_factor.assign(maximum + 1, 0);
  prime[0] = prime[1] = false;

  for (int i = 2; i <= maximum; ++i) {
    if (prime[i]) {
      primes.push_back(i);
      smallest_factor[i] = i;
    }

    for (int j = 0;
         j < (int)primes.size() and (long long) primes[j] * i <= maximum; ++j) {
      prime[primes[j] * i] = false;
      smallest_factor[primes[j] * i] = primes[j];
      if (i % primes[j] == 0) {
        break;
      }
    }
  }
}

// Prime factorizes n in worst case O(sqrt n / log n). Requires having run
// `sieve` up to at least sqrt(n). If we've run `sieve` up to at least n, takes
// O(log n) time.
vector<pair<int64_t, int>> prime_factorize(int64_t n) {
  int64_t sieve_max = int64_t(smallest_factor.size()) - 1;
  assert(1 <= n && n <= sieve_max * sieve_max);
  vector<pair<int64_t, int>> result;

  if (n <= sieve_max) {
    while (n != 1) {
      int64_t p = smallest_factor[n];
      int exponent = 0;

      do {
        n /= p;
        exponent++;
      } while (n % p == 0);

      result.emplace_back(p, exponent);
    }

    return result;
  }

  for (int64_t p : primes) {
    if (p * p > n)
      break;

    if (n % p == 0) {
      result.emplace_back(p, 0);

      do {
        n /= p;
        result.back().second++;
      } while (n % p == 0);
    }
  }

  if (n > 1) {
    result.emplace_back(n, 1);
  }

  return result;
}

int get_prime_exponent(int n) {
  vector<pair<int64_t, int>> prime_factors = prime_factorize(n);
  int sum = 0;

  for (auto &pf : prime_factors) {
    sum += pf.second;
  }

  return sum;
}

// don't need to run `sieve`, set sieved to false
int get_prime_exponent(int64_t n, bool sieved) {
  int sum = 0;
  for (int64_t i = 2; i * i <= n; ++i) {
    while (n % i == 0) {
      sum++;
      n /= i;
    }
  }
  if (n != 1) {
    sum++;
  }
  return sum;
}
// don't need to run `sieve`, set sieved to false
vector<pair<int64_t, int>> prime_factorize(int64_t n, bool sieved) {
  vector<pair<int64_t, int>> result;

  for (int64_t i = 2; i * i <= n; ++i) {
    int exponent = 0;
    while (n % i == 0) {
      n /= i;
      exponent++;
    }
    if (exponent > 0)
      result.emplace_back(i, exponent);
  }
  if (n != 1) {
    result.emplace_back(n, 1);
  }

  return result;
}