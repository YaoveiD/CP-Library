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

// verification https://leetcode-cn.com/submissions/detail/228175390/

auto random_address = [] { char *p = new char; delete p; return uint64_t(p); };
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1));
#define UID(L, R) uniform_int_distribution<int>(L, R)(rng)
#define URD uniform_real_distribution<double>(0.0, 1.0)(rng)

const double CUTOFF = 1e-5;
const double INITIAL = 1e9;
const double STEP = 0.98;
const int ITERATIONS = 10;

template<bool maximum_mode = false>
class simulate_anneal {
private:
    int evaluate(const vector<int>& nums1, const vector<int>& nums2) {
        int result = 0;

        for (int i = 0; i < int(nums1.size()); ++i)
            result += (nums1[i] ^ nums2[i]);

        return result;
    }

    vector<int> neigh_state(const vector<int>& nums) {
        vector<int> neigh = nums;
        
        int i = UID(0, int(nums.size()) - 1);
        int j = UID(0, int(nums.size()) - 1);
        swap(neigh[i], neigh[j]);
        
        return neigh;
    }

    double prob(int last, int current, double temp) {
        if ((current < last) ^ maximum_mode) // we want to minimize
            return 1.0;
        return exp((last - current) / temp);
    }

    int simulate(vector<int>& nums1, vector<int>& nums2) {
        nums2 = neigh_state(nums2);
        int best = evaluate(nums1, nums2);

        for (double temp = INITIAL; temp >= CUTOFF; temp *= STEP) {
            int last = evaluate(nums1, nums2);

            vector<int> new_nums2 = neigh_state(nums2);
            int current = evaluate(nums1, new_nums2);

            if ((current < last) ^ maximum_mode)
                best = current;

            if (prob(last, current, temp) > URD)
                nums2.swap(new_nums2);
        }

        return best;
    }
public:
    int minimumXORSum(vector<int>& nums1, vector<int>& nums2) {
        int best = INT32_MAX;
        for (int iter = 0; iter < ITERATIONS; ++iter)
            best = min(best, simulate(nums1, nums2));
        return best;
    }
};