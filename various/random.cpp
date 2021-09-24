
auto random_address = [] { char *p = new char; delete p; return uint64_t(p); };
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1));
#define UID(L, R) uniform_int_distribution<int>(L, R)(rng)
