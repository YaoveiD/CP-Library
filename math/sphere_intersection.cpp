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

// source : https://chenshouao.github.io/mkdocs/pages/Algorithm/math/sphere_intersection.html
// 给定两球坐标、半径。求相交体积

const double pi = acos(-1);

double dis(double x1, double y1, double z1, double x2, double y2, double z2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2));
}

double volume(double r){
    return 4.0 / 3.0 * pi * r * r * r;
}

double solve(double x1, double y1, double z1,double r1, double x2, double y2, double z2, double r2) {
    double x = dis(x1, y1, z1, x2, y2, z2);
    double m = max(r1, r2); 
    double n = min(r1, r2);
    double ans = 0;

    if(x > r1 + r2) {
        ans = volume(r1) + volume(r2);
    } else if(x + n <= m) {
        ans = volume(m);
    } else {
        ans = volume(r1) + volume(r2) - pi * (n + m - x) * (n + m - x) * (x * x + 2 * x * m - 3 * m * m + 2 * x * n + 6 * m * n - 3 * n * n) / 12 / x;
    }
    return volume(r1) + volume(r2) - ans;
}
