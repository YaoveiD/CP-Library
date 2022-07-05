#include <iostream>
#include <chrono>
using namespace std;

auto start = chrono::steady_clock::now();
// do_something();
auto end = chrono::steady_clock::now();
auto diff = end - start;
#ifdef LOCAL
    cerr << chrono::duration<double, milli>(diff).count() << " ms" << '\n';
#endif