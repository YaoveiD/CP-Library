#include <bits/stdc++.h>
using namespace std;

// source : https://github.com/nealwu/competitive-programming/blob/master/miscellaneous/closest_left_right.cc
// For every i, finds the largest j < i such that `compare(values[j], values[i])` is true, or -1 if no such j exists.
template<typename T, typename T_compare>
std::vector<int> closest_left(const std::vector<T> &values, T_compare &&compare) {
    int n = int(values.size());
    std::vector<int> closest(n);
    std::vector<int> stack;

    for (int i = 0; i < n; i++) {
        while (!stack.empty() && !compare(values[stack.back()], values[i]))
            stack.pop_back();

        closest[i] = stack.empty() ? -1 : stack.back();
        stack.push_back(i);
    }

    return closest;
}

// For every i, finds the smallest j > i such that `compare(values[j], values[i])` is true, or `n` if no such j exists.
template<typename T, typename T_compare>
std::vector<int> closest_right(std::vector<T> values, T_compare &&compare) {
    int n = int(values.size());
    std::vector<int> closest(n);
    std::vector<int> stack;

    for (int i = n - 1; i >= 0; --i) {
        while (!stack.empty() && !compare(values[stack.back()], values[i]))
            stack.pop_back();

        closest[i] = stack.empty() ? n : stack.back();
        stack.push_back(i);
    }

    return closest;
}

// problem: given an array A of size n.
// f(i, j) = max(A_i, A_{i+1}, ..., A_j) - min(A_i, A_{i+1}, ..., A_j)
// compute the sum of f(i, j) for i in [1, n] and j in [i, n].

int main() {
    ios::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(0);
#endif

    int N;
    cin >> N;
    vector<int> A(N);

    for (int &a : A)
        cin >> a;

    auto solve_comp = [&](auto comp_pref, auto comp_suff) -> int64_t {
        vector<int> CL = closest_left(A, comp_pref);
        vector<int> CR = closest_right(A, comp_suff);
        int64_t result = 0;

        for (int i = 0; i < N; ++i)
            result += 1LL * A[i] * (i - CL[i]) * (CR[i] - i);

        return result;
    };

    cout << solve_comp(greater_equal<int>(), greater<int>()) - 
            solve_comp(less_equal<int>(), less<int>()) << '\n';
}
