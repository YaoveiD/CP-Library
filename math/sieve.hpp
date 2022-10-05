// source : https://github.com/nealwu/competitive-programming/blob/master/number_theory/sieve_factor.cc

std::vector<int> smallest_factor;
std::vector<bool> prime;
std::vector<int> primes;

void sieve(int maximum) {
	maximum = std::max(maximum, 1);
	smallest_factor.assign(maximum + 1, 0);
	prime.assign(maximum + 1, true);
	prime[0] = prime[1] = false;
	primes = {};

	for (int p = 2; p <= maximum; p++)
		if (prime[p]) {
			smallest_factor[p] = p;
			primes.push_back(p);

			for (int64_t i = int64_t(p) * p; i <= maximum; i += p)
				if (prime[i]) {
					prime[i] = false;
					smallest_factor[i] = p;
				}
		}
}

// Prime factorizes n in worst case O(sqrt n / log n). Requires having run `sieve` up to at least sqrt(n).
// If we've run `sieve` up to at least n, takes O(log n) time.
std::vector<std::pair<int64_t, int>> prime_factorize(int64_t n) {
	int64_t sieve_max = int64_t(smallest_factor.size()) - 1;
	assert(1 <= n && n <= sieve_max * sieve_max);
	std::vector<std::pair<int64_t, int>> result;

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

	if (n > 1)
		result.emplace_back(n, 1);

	return result;
}

template<typename T>
std::vector<T> generate_factors(const std::vector<std::pair<T, int>> &prime_factors) {
	// See http://oeis.org/A066150 and http://oeis.org/A036451 for upper bounds on number of factors.
	int product = 1;

	for (auto &pf : prime_factors)
		product *= pf.second + 1;

	std::vector<T> factors = {1};
	factors.reserve(product);

	for (auto &pf : prime_factors) {
		T p = pf.first;
		int exponent = pf.second;
		int before_size = int(factors.size());

		for (int i = 0; i < exponent * before_size; i++)
			factors.push_back(factors[factors.size() - before_size] * p);
	}

	assert(int(factors.size()) == product);
	return factors;
}


/*

oeis: A066150
Maximal number of divisors of any n-digit number.
4, 12, 32, 64, 128, 240, 448, 768, 1344, 2304,
4032, 6720, 10752, 17280, 26880, 41472, 64512, 103680, 161280, 245760,
368640, 552960, 860160, 1290240, 1966080,
2764800, 4128768, 6193152, 8957952, 13271040,
19660800, 28311552, 41287680, 59719680, 88473600,
127401984, 181665792, 264241152, 382205952, 530841600
(list; graph; refs; listen; history; text; internal format) 
*/