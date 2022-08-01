ostream &operator<<(ostream &out, __int128 x) {
    if (x == 0) return out << x;
    string res;
    if (x < 0) return out << '-' << -x;
    while (x) {
        res += '0' + x % 10;
        x /= 10;
    }
    std::reverse(res.begin(), res.end());
    return out << res;
}
