using int128_t = __int128;

istream &operator>>(istream &is, int128_t &n) {
    n = 0;
    string s;
    is >> s;
    
    for (auto c : s)
        n = 10 * n + c - '0';

    return is;
}
 
ostream &operator<<(ostream &os, int128_t n) {
    if (n == 0)
        return os << 0;

    string s;

    while (n > 0) {
        s += '0' + n % 10;
        n /= 10;
    }

    reverse(s.begin(), s.end());
    return os << s;
}
 
int128_t gcd(int128_t a, int128_t b) {
    return b ? gcd(b, a % b) : a;
}