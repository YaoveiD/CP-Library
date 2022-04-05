// https://github.com/nealwu/competitive-programming/blob/master/bignum_fft/bignum_fft.cc

struct bignum {
    using value_t = uint16_t;
    static const int SECTION = 4;
    static const value_t BASE = 1e4;
    static const int DOUBLE_DIV_SECTIONS = 5;

    static const uint64_t U64_BOUND = numeric_limits<uint64_t>::max() - uint64_t(BASE) * BASE;
    static const uint64_t BASE_OVERFLOW_CUTOFF = numeric_limits<uint64_t>::max() / BASE;

    static int highest_bit(unsigned x) {
        return x == 0 ? -1 : 31 - __builtin_clz(x);
    }

    vector<value_t> values;

    bignum(uint64_t x = 0) {
        init(x);
    }

    bignum(string str) {
        int len = int(str.size());
        int num_values = max((len + SECTION - 1) / SECTION, 1);
        values.assign(num_values, 0);

        int counter = 0;
        int index = 0;
        value_t p10 = 1;

        for (int i = len - 1; i >= 0; i--) {
            assert('0' <= str[i] && str[i] <= '9');
            values[index] = value_t(values[index] + p10 * (str[i] - '0'));

            if (++counter >= SECTION) {
                counter = 0;
                index++;
                p10 = 1;
            } else {
                p10 = value_t(10 * p10);
            }
        }

        trim_check();
    }

    explicit operator uint64_t() const {
        uint64_t integer_value = 0;

        for (int i = int(values.size()) - 1; i >= 0; i--)
            integer_value = BASE * integer_value + values[i];

        return integer_value;
    }

    void trim_check() {
        while (values.size() > 1 && values.back() == 0)
            values.pop_back();

        if (values.empty())
            values = {0};
    }

    void checked_add(size_t position, uint64_t add) {
        if (position >= values.size())
            values.resize(position + 1, 0);

        values[position] = value_t(values[position] + add);
    }

    void init(uint64_t x) {
        values.clear();

        do {
            checked_add(values.size(), x % BASE);
            x /= BASE;
        } while (x > 0);
    }

    string to_string() const {
        string result = "";

        for (value_t v : values)
            for (int i = 0; i < SECTION; i++) {
                result += char('0' + v % 10);
                v = value_t(v / 10);
            }

        while (result.size() > 1 && result.back() == '0')
            result.pop_back();

        reverse(result.begin(), result.end());
        return result;
    }

    int compare(const bignum &other) const {
        int n = int(values.size());
        int m = int(other.values.size());

        if (n != m)
            return n < m ? -1 : +1;

        for (int i = n - 1; i >= 0; i--)
            if (values[i] != other.values[i])
                return values[i] < other.values[i] ? -1 : +1;

        return 0;
    }

    bool operator<(const bignum &other) const { return compare(other) < 0; }
    bool operator>(const bignum &other) const { return compare(other) > 0; }
    bool operator<=(const bignum &other) const { return compare(other) <= 0; }
    bool operator>=(const bignum &other) const { return compare(other) >= 0; }
    bool operator==(const bignum &other) const { return compare(other) == 0; }
    bool operator!=(const bignum &other) const { return compare(other) != 0; }

    // Multiplies this number by BASE^p.
    bignum operator<<(int p) const {
        assert(p >= 0);
        int n = int(values.size());

        bignum result;
        result.values.resize(n + p, 0);

        for (int i = 0; i < n; i++)
            result.values[i + p] = values[i];

        result.trim_check();
        return result;
    }

    // Divides this number by BASE^p.
    bignum operator>>(int p) const {
        assert(p >= 0);
        int n = int(values.size());

        if (p >= n)
            return bignum(0);

        bignum result;
        result.values.resize(n - p);

        for (int i = 0; i < n - p; i++)
            result.values[i] = values[i + p];

        result.trim_check();
        return result;
    }

    // Returns the bignum represented by values[a, b).
    bignum range(int a, int b = -1) const {
        if (b == -1)
            b = int(values.size());

        assert(a <= b);
        bignum result;
        result.values.resize(b - a);

        for (int i = 0; i < b - a; i++)
            result.values[i] = values[i + a];

        result.trim_check();
        return result;
    }

    bignum& operator+=(const bignum &other) {
        int n = int(other.values.size());

        for (int i = 0, carry = 0; i < n || carry > 0; i++) {
            checked_add(i, (i < n ? other.values[i] : 0) + carry);

            if (values[i] >= BASE) {
                values[i] = value_t(values[i] - BASE);
                carry = 1;
            } else {
                carry = 0;
            }
        }

        trim_check();
        return *this;
    }

    bignum& operator-=(const bignum &other) {
        assert(*this >= other);
        int n = int(other.values.size());

        for (int i = 0, carry = 0; i < n || carry > 0; i++) {
            value_t subtract = value_t((i < n ? other.values[i] : 0) + carry);

            if (values[i] < subtract) {
                values[i] = value_t(values[i] + BASE - subtract);
                carry = 1;
            } else {
                values[i] = value_t(values[i] - subtract);
                carry = 0;
            }
        }

        trim_check();
        return *this;
    }

    friend bignum operator+(const bignum &a, const bignum &b) { return bignum(a) += b; }
    friend bignum operator-(const bignum &a, const bignum &b) { return bignum(a) -= b; }

    friend bignum operator*(const bignum &a, const bignum &b) {
        int n = int(a.values.size());
        int m = int(b.values.size());

        if (n > m)
            return b * a;

        // Standard quadratic-time multiplication, optimized for minimal division.
        bignum product;
        product.values.resize(n + m - 1, 0);
        uint64_t value = 0, carry = 0;

        for (int index_sum = 0; index_sum < n + m - 1 || carry > 0; index_sum++) {
            value = carry % BASE;
            carry /= BASE;

            for (int i = max(0, index_sum - (m - 1)); i <= min(n - 1, index_sum); i++) {
                value += uint64_t(a.values[i]) * b.values[index_sum - i];

                if (value > U64_BOUND) {
                    carry += value / BASE;
                    value %= BASE;
                }
            }

            carry += value / BASE;
            value %= BASE;
            product.checked_add(index_sum, value);
        }

        product.trim_check();
        return product;
    }

    bignum& operator*=(const bignum &other) {
        return *this = *this * other;
    }

    bignum operator*(uint64_t mult) const {
        if (mult == 0)
            return 0;

        if (mult >= BASE_OVERFLOW_CUTOFF)
            return *this * bignum(mult);

        int n = int(values.size());

        bignum product;
        product.values.resize(n + 1, 0);
        uint64_t carry = 0;

        for (int i = 0; i < n || carry > 0; i++) {
            uint64_t value = mult * (i < n ? values[i] : 0) + carry;
            carry = value / BASE;
            value %= BASE;
            product.checked_add(i, value);
        }

        product.trim_check();
        return product;
    }

    bignum& operator*=(uint64_t mult) {
        return *this = *this * mult;
    }

    double estimate_div(const bignum &other) const {
        int n = int(values.size());
        int m = int(other.values.size());
        double estimate = 0, other_estimate = 0;
        int count = 0, other_count = 0;
        double p_base = 1;

        for (int i = n - 1; i >= 0 && count < DOUBLE_DIV_SECTIONS; i--) {
            estimate = estimate + p_base * double(values[i]);
            p_base /= BASE;
            count++;
        }

        p_base = 1;

        for (int i = m - 1; i >= 0 && other_count < DOUBLE_DIV_SECTIONS; i--) {
            other_estimate = other_estimate + p_base * double(other.values[i]);
            p_base /= BASE;
            other_count++;
        }

        return estimate / other_estimate * pow(BASE, n - m);
    }

    pair<bignum, bignum> div_mod(const bignum &other) const {
        assert(other > 0);

        int n = int(values.size());
        int m = int(other.values.size());
        bignum quotient = 0;
        bignum remainder = *this;

        for (int i = n - m; i >= 0; i--) {
            // This is possible due to remainder.trim_check() below.
            if (i >= int(remainder.values.size()))
                continue;

            bignum chunk = remainder.range(i);

            // Compute floor(chunk / other) precisely.
            uint64_t div = uint64_t(chunk.estimate_div(other) + 1e-7);
            bignum mult = other * div;

            while (div > 0 && mult > chunk) {
                // cerr << "Decrementing " << div << " (" << i << ")" << '\n';;
                mult -= other;
                div--;
            }

            while (div < BASE - 1 && mult + other <= chunk) {
                // cerr << "Incrementing " << div << " (" << i << ")" << '\n';
                mult += other;
                div++;
            }

            remainder -= mult << i;
            remainder.trim_check();

            if (div > 0)
                quotient.checked_add(i, div);
        }

        quotient.trim_check();
        remainder.trim_check();
        return make_pair(quotient, remainder);
    }

    friend bignum operator/(const bignum &a, const bignum &b) { return a.div_mod(b).first; }
    friend bignum operator%(const bignum &a, const bignum &b) { return a.div_mod(b).second; }

    bignum& operator/=(const bignum &other) { return *this = *this / other; }
    bignum& operator%=(const bignum &other) { return *this = *this % other; }

    pair<bignum, uint64_t> div_mod(uint64_t denom) const {
        assert(denom > 0);

        // Make sure denom * BASE doesn't overflow.
        if (denom >= BASE_OVERFLOW_CUTOFF) {
            pair<bignum, bignum> p = div_mod(bignum(denom));
            return make_pair(p.first, uint64_t(p.second));
        }

        int n = int(values.size());
        bignum quotient = 0;
        uint64_t remainder = 0;

        for (int i = n - 1; i >= 0; i--) {
            remainder = BASE * remainder + values[i];

            if (remainder >= denom) {
                quotient.checked_add(i, remainder / denom);
                remainder %= denom;
            }
        }

        quotient.trim_check();
        return make_pair(quotient, remainder);
    }

    bignum operator/(uint64_t denom) const {
        return div_mod(denom).first;
    }

    uint64_t operator%(uint64_t denom) const {
        assert(denom > 0);

        if (BASE % denom == 0) {
            assert(!values.empty());
            return values[0] % denom;
        }

        // Make sure denom * BASE doesn't overflow.
        if (denom >= BASE_OVERFLOW_CUTOFF)
            return uint64_t(div_mod(bignum(denom)).second);

        int n = int(values.size());
        uint64_t remainder = 0;

        for (int i = n - 1; i >= 0; i--) {
            remainder = BASE * remainder + values[i];

            if (remainder >= BASE_OVERFLOW_CUTOFF)
                remainder %= denom;
        }

        remainder %= denom;
        return remainder;
    }

    bignum& operator/=(uint64_t denom) { return *this = *this / denom; }
    bignum& operator%=(uint64_t denom) { return *this = *this % denom; }

    bignum& operator++() { return *this += 1; }
    bignum& operator--() { return *this -= 1; }

    bignum operator++(int) { bignum before = *this; ++*this; return before; }
    bignum operator--(int) { bignum before = *this; --*this; return before; }

    bignum power(int exponent) const {
        assert(exponent >= 0);
        bignum result = 1;

        if (exponent == 0)
            return result;

        for (int k = highest_bit(exponent); k >= 0; k--) {
            result *= result;

            if (exponent >> k & 1)
                result *= *this;
        }

        return result;
    }

    friend ostream& operator<<(ostream &os, const bignum &x) {
        return os << x.to_string();
    }

    static bignum mod_pow(bignum a, bignum b, const bignum &mod) {
        vector<bool> bits;

        while (b != 0) {
            bits.push_back(b % 2);
            b /= 2;
        }

        int n = int(bits.size());
        int k = 1;

        while (2 * k << k < n)
            k++;

        vector<bignum> cached(1 << k);
        cached[0] = 1;
        cached[1] = a;

        for (int i = 2; i < 1 << k; i++)
            cached[i] = cached[i - 1] * a % mod;

        bignum result = 1;
        int power = 0;

        for (int i = n - 1; i >= 0; i--) {
            power = 2 * power + bits[i];
            result = result * result % mod;

            if (2 * power >= 1 << k || i == 0) {
                result = result * cached[power] % mod;
                power = 0;
            }
        }

        return result;
    }

    bool miller_rabin(int iterations = 20) const {
        const bignum &n = *this;

        if (n < 2)
            return false;

        static const uint64_t SMALL_PRIMES[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
        uint64_t product = 1;

        for (uint64_t p : SMALL_PRIMES) {
            if (n == p)
                return true;

            product *= p;
        }

        uint64_t remainder = n % product;

        for (uint64_t p : SMALL_PRIMES)
            if (remainder % p == 0)
                return false;

        int r = 0;
        bignum d = n - 1;

        while (d % 2 == 0) {
            r++;
            d /= 2;
        }

        auto random_address = [] { char *p = new char; delete p; return uint64_t(p); };
        static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1));
        uint64_t a_max = n < bignum(UINT64_MAX) + 2 ? uint64_t(n - 2) : UINT64_MAX;
        assert(n - 2 >= a_max);

        for (int k = 0; k < iterations; k++) {
            bignum a = uniform_int_distribution<uint64_t>(2, a_max)(rng);
            bignum x = mod_pow(a, d, n);

            if (x == 1 || x == n - 1)
                continue;

            bool witness = true;

            for (int i = 0; i < r - 1 && witness; i++) {
                x = x * x % n;

                if (x == n - 1)
                    witness = false;
            }

            if (witness)
                return false;
        }

        return true;
    }
};