#include <bits/stdc++.h>

// Solution to https://www.luogu.com.cn/problem/P3796.s
namespace AC {
const int A = 26;
const int NN = 80 * 150 * A;
int trans[NN][A];
int fail[NN];
int index[NN];
int cnt[NN];
int vis[NN];
int sz;

void insert(const std::string &word, int j) {
	int n = 0;
	for (char _c : word) {
		int c = _c - 'a';
		if (!trans[n][c]) {
			index[sz] = -1;
			trans[n][c] = sz++;
		}
		n = trans[n][c];
	}
	index[n] = j;
}

// Returns the BFS order of Trie(just for convenient).
std::vector<int> build() {
	std::vector<int> que;

	for (int a = 0; a < A; ++a)
		if (trans[0][a])
			que.push_back(trans[0][a]);

	for (int i = 0; i < int(que.size()); ++i) {
		int n = que[i];

		for (int a = 0; a < A; ++a)
			if (trans[n][a]) {
				fail[trans[n][a]] = trans[fail[n]][a];
				que.push_back(trans[n][a]);
			} else {
				trans[n][a] = trans[fail[n]][a];
			}
	}

	return que;
}

// For each `pattern`, find how many times it occurs in `str`.
// cnt[i] = the occurence of the i-th pattern.
// Works in O(sum(|pattern|) + |str|) ?
void findAll(const std::string &str) {
	std::vector<int> order = build();
	int n = 0;
	for (char _c : str) {
		int c = _c - 'a';
		n = trans[n][c];
		vis[n]++;
	}

	reverse(order.begin(), order.end());
	for (int i : order) {
		vis[fail[i]] += vis[i];
	}

	for (int i = 0; i < sz; ++i)
		if (index[i] != -1)
			cnt[index[i]] = vis[i];
}

void init() {
	index[0] = -1;
	for (int i = 0; i < sz; ++i) {
		memset(trans[i], 0, sizeof trans[i]);
		fail[i] = 0;
		cnt[i] = 0;
		vis[i] = 0;
	}
	sz = 1;
}
} // namespace AhoCorasick

int main() {
	using namespace std;
	ios_base::sync_with_stdio(false), cin.tie(nullptr);

	int nt;
	while (cin >> nt) {
		if (nt == 0)
			break;

		AC::init();
		vector<string> T(nt);

		for (int i = 0; i < nt; ++i) {
			cin >> T[i];
			AC::insert(T[i], i);
		}

		string S; cin >> S;
		AC::findAll(S);
		int most = *max_element(AC::cnt, AC::cnt + nt);
		cout << most << '\n';

		for (int i = 0; i < nt; ++i)
			if (AC::cnt[i] == most)
				cout << T[i] << '\n';
	}
}

