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

// source : https://chenshouao.github.io/mkdocs/pages/Algorithm/math/ternary_search.html

using LL = long long;

const double eps = 1e-8;
const LL INF = 100000000000000;

double evaluate(LL x) {
    //this is a function whose value was determine by x
    return 0;
}

double ternary_search_min(LL low, LL high) {
    //求凹函数最小值
    double ans = INF;
    while (low < high) {
        LL m1 = (2 * low + high) / 3;
        LL m2 = (2 * high + low + 2) / 3;
        if (evaluate(m1) < evaluate(m2)) {
            ans = min(ans, evaluate(m1));
            high = m2 - 1;
        } else {
            ans = min(ans, evaluate(m2));
            low = m1 + 1;
        }
    }
    return ans;
}

double ternary_search_max(LL low, LL high) {
    //求凸函数最大值
    double ans = -INF;
    while (low < high) {
        LL m1 = (2 * low + high) / 3;
        LL m2 = (2 * high + low + 2) / 3;
        if (evaluate(m1) > evaluate(m2)) {
            ans = max(ans, evaluate(m1));
            high = m2 - 1;
        } else {
            ans = max(ans, evaluate(m2));
            low = m1 + 1;
        }
    }
    return ans;
}

double ternary_search(double low, double high) {
    //求凸函数最大值
    double rmid, mid;
    while (fabs(high - low) > eps) {
        mid = (low + high) / 2;
        rmid = (mid + high) / 2;
        if (evaluate(mid) > evaluate(rmid)) {
            high = rmid;
        } else {
            low = mid;
        }
    }
    return evaluate(low);
}