#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdlib>
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
// verification https://www.luogu.com.cn/record/59921549

auto random_address = [] { char *p = new char; delete p; return uint64_t(p); };
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1));
#define UID(L, R) uniform_int_distribution<int>(L, R)(rng)
#define URD uniform_real_distribution<double>(0.0, 1.0)(rng)

const double CUTOFF = 1e-15;
const double INITIAL = 3412;
const double STEP = 0.996;
const int ITERATIONS = 10;
const int MX = 37823899;

struct stuff {
    int x, y, w;
};

int N;
vector<stuff> A;

struct state {
    double x, y;

    state(double _x = 0, double _y = 0) : x(_x), y(_y) {}
};

template<typename T, bool maximum_mode = false>
class simulate_anneal {
private:
    double dist(double x, double y) {
        return sqrt(x * x + y * y);
    }

    T evaluate(const state& s) {
        double E = 0;

        for (const auto& a : A)
            E += a.w * dist(a.x - s.x, a.y - s.y);

        return E;
    }

    state neigh_state(const state& curr, double temp) {
        double dx = (rand() * 2 - RAND_MAX) * temp;
        double dy = (rand() * 2 - RAND_MAX) * temp;

        return state(curr.x + dx, curr.y + dy);
    }

    double prob(T last, T current, double temp) {
        if ((current < last) ^ maximum_mode) // we want to minimize
            return 1.0;
        return exp((last - current) / temp);
    }

    void simulate(const state& _src) {
        state src = _src;

        for (double temp = INITIAL; temp > CUTOFF; temp *= STEP) {
            T last = evaluate(src);

            state new_state = neigh_state(src, temp);
            T current = evaluate(new_state);

            if ((current < last) ^ maximum_mode) {
                best = current;
                finally = new_state;
            }

            if (prob(last, current, temp) > URD)
                swap(src, new_state);
        }
    }
public:
    state finally;
    T best = 1e20;

    simulate_anneal() {}

    state solve(const state& _initial) {
        for (int iter = 0; iter < ITERATIONS; ++iter)
            simulate(finally);

        return finally;
    }
};

int main() {
    ios::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(0);
#endif
    cout << fixed << setprecision(3);

    cin >> N;
    A.resize(N);
    for (stuff& a : A)
        cin >> a.x >> a.y >> a.w;

    simulate_anneal<double> SA;
    state initial;
    state finally = SA.solve(initial);

    cout << finally.x << ' ' << finally.y << '\n';
}