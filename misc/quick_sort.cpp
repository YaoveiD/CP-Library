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

class Solution {
private:
    int partition(vector<int>& nums, int L, int R) {
        int piovt = nums[R];
        int i = L - 1;
        for (int j = L; j < R; ++j) {
            if (nums[j] <= piovt) {
                i += 1;
                swap(nums[j], nums[i]);
            }
        }
        swap(nums[i + 1], nums[R]);
        return i + 1;
    }

    int randomized_partition(vector<int>& nums, int L, int R) {
        int i = rand() % (R - L + 1) + L;
        swap(nums[i], nums[R]);
        return partition(nums, L, R);
    }

    void kth_element(vector<int>& nums, int L, int R, int k) {
        if (L >= R) {
            return;
        }
        int pos = randomized_partition(nums, L, R);
        int count = pos - L + 1;
        if (count == k) {
            return;
        } else if (count < k) {
            kth_element(nums, pos + 1, R, k - count);
        } else {
            kth_element(nums, L, pos - 1, k);
        }
    }

    void quick_sort(vector<int>& arr, int L, int R) {
        if (L >= R) {
            return;
        }
        int pos = randomized_partition(arr, L, R);
        quick_sort(arr, L, pos - 1);
        quick_sort(arr, pos + 1, R);
    }
public:
    vector<int> smallestK(vector<int>& arr, int K) {
        if (min((int) arr.size(), K) == 0) {
            return vector<int>();
        }

        // nth_element(arr.begin(), arr.begin() + K - 1, arr.end());
        kth_element(arr, 0, (int) arr.size() - 1, K);

        vector<int> result(arr.begin(), arr.begin() + K);
        return result;
    }

    // pretty slow compared with std::sort();
    void quick_sort(vector<int>& arr) {
        return quick_sort(arr, 0, (int) arr.size() - 1);
    }
};

int main() {
    vector<int> arr = {1, 5, 3, 2, 4, 6};

    Solution sol;
    sol.quick_sort(arr);

    for (int x : arr) {
        cout << x << '\n';
    }

    return 0;
}