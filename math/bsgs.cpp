// Find the smallest `n` such that a^n == b (mod p)
// Returns -1 if there is no such `n`
int bsgs(int64_t a, int64_t b, int p){
	std::unordered_map<int,int> mp;
	int s = sqrt(p) + 1;
	int64_t cur = 1;

	for (int B = 0; B < s; ++B) {
		mp[cur * b % p] = B;
		cur = cur * a % p;
	}

	int64_t now = cur;

	for (int A = 1; A <= s; ++A) {
		auto it = mp.find(now);

		if (it != mp.end())
			return A * s - it->second;

		now = now * cur % p;
	}

	return -1;
}