/*
* author:  yaoveil
* created: 2021-08-15 22:30:48
*/

#include <iostream>
#include <chrono>
 
using namespace std;

  auto start = chrono::steady_clock::now();

  int tt = 1;
  //cin >> tt;
  while (tt--) {
    solve();
  }

  auto end = chrono::steady_clock::now();
  auto diff = end - start;
#ifdef LOCAL
  cerr << chrono::duration <double, milli> (diff).count() << " ms" << '\n';
#endif 