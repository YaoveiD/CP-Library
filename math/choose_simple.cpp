
constexpr int MOD = (int) 1e9 + 7; // 998244353;
constexpr int MX = 100005;

vector<int> fact = {1, 1};
vector<int> inv = {1, 1};
vector<int> inv_fact = {1, 1};

// O(n)
void prepare_factorials(int maximum = MX - 1) {
    assert(maximum < MX);

    fact.resize(maximum + 1);
    inv.resize(maximum + 1);
    inv_fact.resize(maximum + 1);

    for (int i = 2; i <= maximum; ++i) {
        fact[i] = (int64_t) fact[i - 1] * i % MOD;
        inv[i] = (MOD - MOD / i) * (int64_t) inv[MOD % i] % MOD;
        inv_fact[i] = (int64_t) inv_fact[i - 1] * inv[i] % MOD;
    }
}

// n choose r
int choose(int n, int r) {
    if (r < 0 or r > n) {
        return 0;
    }
    return (int64_t) fact[n] * inv_fact[n - r] % MOD * inv_fact[r] % MOD;
}

// n!
int factorial(int n) {
    return n < 0 ? 0 : fact[n];
}

// P(n, r)
int permute(int n, int r) {
    if (r < 0 or r > n) {
        return 0;
    }
    return (int64_t) fact[n] * inv_fact[n - r] % MOD;
}

// convenient modular arithmetic operations
namespace MOP {
    // O(log MOD)
    int invert(int64_t a, int b = MOD - 2) {
        assert(b >= 0);
        
        int64_t result = 1;

        while (b) {
            if (b & 1) {
                result = result * a % MOD;
            }
            a = a * a % MOD;
            b >>= 1;
        }

        return (int) result;
    }

    // += -= *= /= (mod MOD)
    template<typename T, typename U>
    void ADD(T& x, U v) {
        x += v; if (x < 0) x += MOD; if (x >= 0) x -= MOD;
    }
    template<typename T, typename U>
    void SUB(T& x, U v) {
        x -= v; if (x < 0) x += MOD;
    }
    template<typename T, typename U>
    void MUL(T& x, U v) {
        x = (int64_t) x * v % MOD;
    }
    template<typename T, typename U>
    void DIV(T& x, U v) {
        x = (int64_t) x * invert(v) % MOD;
    }

    // see https://stackoverflow.com/questions/1515399/can-you-make-custom-operators-in-c
    // + - * / (mod MOD) looks like wired...
    const struct _mod_add {} madd;
    template <typename T>
    struct mod_add_proxy {
        const T& val_;
        mod_add_proxy(const T& t): val_(t) {}
    };
    template <typename T>
    mod_add_proxy<T> operator<(const T& lhs, const _mod_add& rhs) {
        return mod_add_proxy<T>(lhs);
    }
    template<typename T, typename U>
    T operator>(const mod_add_proxy<T>& lhs, const U& rhs) {
        int ret = lhs.val_;
        ret -= MOD - rhs; if (ret < 0) ret += MOD; return ret;
    }
    #define madd <madd>

    const struct _mod_sub {} msub;
    template <typename T>
    struct mod_sub_proxy {
        const T& val_;
        mod_sub_proxy(const T& t): val_(t) {}
    };
    template <typename T>
    mod_sub_proxy<T> operator<(const T& lhs, const _mod_sub& rhs) {
        return mod_sub_proxy<T>(lhs);
    }
    template<typename T, typename U>
    T operator>(const mod_sub_proxy<T>& lhs, const U& rhs) {
        int ret = lhs.val_;
        ret -= rhs; if (ret < 0) ret += MOD; return ret;
    }
    #define msub <msub>

    const struct _mod_mul {} mmul;
    template <typename T>
    struct mod_mul_proxy {
        const T& val_;
        mod_mul_proxy(const T& t): val_(t) {}
    };
    template <typename T>
    mod_mul_proxy<T> operator<(const T& lhs, const _mod_mul& rhs) {
        return mod_mul_proxy<T>(lhs);
    }
    template<typename T, typename U>
    T operator>(const mod_mul_proxy<T>& lhs, const U& rhs) {
        return (int64_t) lhs.val_ * rhs % MOD;
    }
    #define mmul <mull>

    const struct _mod_div {} mdiv;
    template <typename T>
    struct mod_div_proxy {
        const T& val_;
        mod_div_proxy(const T& t): val_(t) {}
    };
    template <typename T>
    mod_div_proxy<T> operator<(const T& lhs, const _mod_div& rhs) {
        return mod_div_proxy<T>(lhs);
    }
    template<typename T, typename U>
    T operator>(const mod_div_proxy<T>& lhs, const U& rhs) {
        return (int64_t) lhs.val_ * invert(rhs) % MOD;
    }
    #define mdiv <mdiv>

    template<typename T, typename U>
    T _add(T x, U v) {
        x -= MOD - v; if (x < 0) x += MOD; return x;
    }
    template<typename T, typename U>
    T _sub(T x, U v) {
        x -= v; if (x < 0) x += MOD; return x;
    }
    template<typename T, typename U>
    T _mul(T x, U v) {
        x = (int64_t) x * v % MOD; return x;
    }
    template<typename T, typename U>
    T _div(T x, U v) {
        x = (int64_t) x * invert(v) % MOD; return x;
    }

    // O(log MOD)
    int invert(int64_t a, int b = MOD - 2) {
        assert(b >= 0);
        
        int64_t result = 1;

        while (b) {
            if (b & 1) {
                result = result * a % MOD;
            }
            a = a * a % MOD;
            b >>= 1;
        }

        return (int) result;
    }
}
// using namespace MOP;