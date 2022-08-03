auto random_address = [] { char *p = new char; delete p; return uint64_t(p); };
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1));
#define UID(L, R) std::uniform_int_distribution<int>(L, R)(rng)
#define URD std::uniform_real_distribution<double>(0.0, 1.0)(rng)
