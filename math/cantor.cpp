#include <bits/stdc++.h>
using namespace std;

// I mean, useless algorithm
// all of these start from 0

const int N_MAX = 21;
int64_t facts[N_MAX] = {1};

// returns the 0-started order of a permutation in O(n^2) time.
// can be optimized to O(nlogn) by fenwick tree if needed.
int64_t cantor(const vector<int>& permutation) {
	int n = int(permutation.size());
	int64_t encoding = 0;
	vector<int> suffix_less_count(n);

	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j)
			if (permutation[i] > permutation[j])
				suffix_less_count[i]++;

	for (int i = 0; i < n; ++i)
		encoding += suffix_less_count[i] * facts[n - i - 1];

	return encoding;
}

// returns a n-permutation whose order is order(0-started).
// can be optimized by bst
vector<int> decantor(int64_t order, int n) {
	vector<int> suffix_less_count(n);

	for (int i = 0; i < n; ++i) {
		suffix_less_count[i] = order / facts[n - i - 1];
		order -= facts[n - i - 1] * suffix_less_count[i];
	}

	vector<int> rest(n);
	iota(rest.begin(), rest.end(), 0);
	vector<int> perm(n);

	for (int i = 0; i < n; ++i) {
		perm[i] = rest[suffix_less_count[i]];
		rest.erase(lower_bound(rest.begin(), rest.end(), perm[i]));
	}

	return perm;
}

void prepare_facts() {
	for (int i = 1; i < N_MAX; ++i)
		facts[i] = facts[i - 1] * i;
}

int main() {
	prepare_facts();

	vector<int> perm(4);
	iota(perm.begin(), perm.end(), 0);

	do {
		debug(perm, cantor(perm));
		int c = cantor(perm);
		assert(decantor(c, 4) == perm);
	} while (next_permutation(perm.begin(), perm.end()));
}
