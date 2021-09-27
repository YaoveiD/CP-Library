
constexpr int MOD = int(1e9) + 7;
int64_t modpow(int64_t a, int64_t b) {
  assert(b >= 0);

  int64_t result = 1;
  
  while (b) {
    if (b & 1) {
      result = result * a % MOD;
    }
    a = a * a % MOD;
    b >>= 1;
  }
  
  return result;
}
