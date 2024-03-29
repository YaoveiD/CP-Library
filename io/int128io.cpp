std::ostream &operator<<(std::ostream &out, __int128 x) {
    if (x == 0) return out << 0;
    if (x < 0) return out << '-' << -x;
	std::string res;
    while (x) {
        res += '0' + x % 10;
        x /= 10;
    }
    reverse(res.begin(), res.end());
    return out << res;
}
