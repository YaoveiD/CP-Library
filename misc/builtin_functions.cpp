/*
 * author:  yaoveil
 * created: 2021-08-17 21:59:30
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

// make sure to initialize all global vars
// uncomment cin >> tt?
void test() {
	// _builtin_popcount(x): This function is used to count the number of
	// one’s(set bits) in an integer.
	int N = 6;
	cout << "Count of 1s in binary of " << N << " is " << __builtin_popcount(N)
			 << '\n';

	// _builtin_parity(x): This function is used to check the parity of a number.
	// This function returns true(1) if the number has odd parity else it returns
	// false(0) for even parity.
	cout << "Parity of 1s in binary of " << N << " is " << __builtin_parity(N)
			 << '\n';

	// __builtin_clz(x): This function is used to count the leading zeros of the
	// integer. Note : clz = count leading zero’s Example: It counts number of
	// zeros before the first occurrence of one(set bit).

	// __builtin_ctz(x): This function is used to count the trailing zeros of the
	// given integer. Note : ctz = count trailing zeros. Example: Count no of
	// zeros from last to first occurrence of one(set bit).
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int tt = 1;
	// cin >> tt;
	while (tt--) {
		test();
	}

	return 0;
}
