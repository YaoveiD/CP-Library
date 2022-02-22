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

// source : https://github.com/nealwu/competitive-programming/blob/master/number_theory/sieve_linear.cc
vector<int> smallest_factor;
vector<bool> prime;
vector<int> primes;

// Note: this sieve is O(n), but the constant factor is worse than the O(n log log n) sieve due to the multiplication.
void sieve(int maximum) {
    maximum = max(maximum, 1);
    smallest_factor.assign(maximum + 1, 0);
    prime.assign(maximum + 1, true);
    prime[0] = prime[1] = false;
    primes = {};

    for (int i = 2; i <= maximum; i++) {
        if (prime[i]) {
            smallest_factor[i] = i;
            primes.push_back(i);
        }

        for (int p : primes) {
            if (p > smallest_factor[i] || int64_t(i) * p > maximum)
                break;

            prime[i * p] = false;
            smallest_factor[i * p] = p;
        }
    }
}