#include <bits/stdc++.h>
using namespace std;

// source : https://chenshouao.github.io/mkdocs/pages/Algorithm/math/ternary_search.html
using LL = long long;

template<typename res_t, typename F>
res_t ternary_search_min(LL low, LL high, F &&evaluate) {
    //求凹函数最小值
    res_t ans = numeric_limits<res_t>::max;
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

template<typename res_t, typename F>
res_t ternary_search_max(LL low, LL high, F &&evaluate) {
    //求凸函数最大值
    res_t ans = numeric_limits<res_t>::lowest;
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

template<typename F>
double ternary_search(double low, double high, F &&evaluate) {
    //求凸函数最大值
    const double eps = 1e-8;
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

// I don't konw if it works better.
template<typename F>
LL ternary_search_min(LL low, LL high, F &&evaluate) {
    while (low < high) {
        LL mid = low + (high - low) / 2;

        if (evaluate(mid) < evaluate(mid + 1))
            high = mid;
        else
            low = mid + 1;
    }

    return evaluate(low);
}