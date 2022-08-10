// source : inspired by https://www.luogu.com.cn/problem/solution/P3870 Juan_feng
// verfication : https://judge.yosupo.jp/submission/99703

namespace IO {
inline char nc() {
    static const int BUFFER_SIZE = 1 << 15;
    static char buf[BUFFER_SIZE], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, BUFFER_SIZE, stdin), p1 == p2) ? EOF : *p1++; 
}

template<typename T> inline void read(T& num) {
    num = 0;
    char digit = nc();
    bool negtive = false;

    for (; !isdigit(digit); digit = nc())
        negtive ^= !(digit ^ 45);

    for (; isdigit(digit); digit = nc())
        num = num * 10 + digit - '0';
}

template<typename T, typename... Ts>
inline void read(T& t, Ts&... ts) {
    read(t); read(ts...);
}
} // namespace IO
