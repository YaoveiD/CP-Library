const int MOD = 1000000007; // 998244353;

std::vector<int64_t> fact = {1, 1};
std::vector<int64_t> inv = {1, 1};
std::vector<int64_t> inv_fact = {1, 1};

void prepare_factorials(int maximum) {
	int before = int(fact.size());
	fact.resize(maximum + 1);
	inv.resize(maximum + 1);
	inv_fact.resize(maximum + 1);

	for (int i = before; i <= maximum; ++i) {
		fact[i] = fact[i - 1] * i % MOD;
		inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
		inv_fact[i] = inv_fact[i - 1] * inv[i] % MOD;
	}
}

// n choose r
int64_t choose(int n, int r) {
	if (r < 0 || r > n)
		return 0;
	return fact[n] * inv_fact[n - r] % MOD * inv_fact[r] % MOD;
}

// n!
int64_t factorial(int n) {
	return n < 0 ? 0 : fact[n];
}

// P(n, r)
int64_t permute(int n, int r) {
	if (r < 0 || r > n)
		return 0;
	return fact[n] * inv_fact[n - r] % MOD;
}
