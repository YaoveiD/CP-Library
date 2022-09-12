std::vector<bool> prime;
std::vector<int> primes;
std::vector<int> phi;

void sieve(int maximum) {
    maximum = std::max(maximum, 1);
    prime.assign(maximum + 1, true);
    phi.resize(maximum + 1);
    prime[0] = prime[1] = false;
    primes = {};
    phi[1] = 1;

    for (int p = 2; p <= maximum; ++p) {
        if (prime[p]) {
            primes.push_back(p);
            phi[p] = p - 1;
        }

        for (int j = 0; j < int(primes.size()) && int64_t(primes[j]) * p <= maximum; ++j) {
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
