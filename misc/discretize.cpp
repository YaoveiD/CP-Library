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

// discretize a sequence of integers
template<typename T_iterable>
void discretize(T_iterable& seq, int start = 1) {
    T_iterable sorted = seq;
    sort(sorted.begin(), sorted.end());
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());

    for (auto&& item : seq) {
        item = lower_bound(sorted.begin(), sorted.end(), item) - sorted.begin() + start;
    }
}

template<typename T, typename T_iterable>
map<T, int> compress(const T_iterable& seq, int start = 1) {
    set<T> values;
    for (const auto& item : seq) {
        values.insert(item);
    }

    map<T, int> comp;
    for (const auto& value : values)
        comp[value] = start++;

    return comp;
}
