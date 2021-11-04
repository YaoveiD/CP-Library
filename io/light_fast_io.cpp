#include <iostream>

// fast input light version
// source : https://www.luogu.com.cn/problem/solution/P3870 Juan_feng
// verification : https://www.luogu.com.cn/problem/P1001

const int BUFFER_SIZE = 1 << 15;
inline char nc() {
    static char buf[BUFFER_SIZE], *p1=buf, *p2=buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, BUFFER_SIZE, stdin), p1 == p2) ? EOF : *p1++; 
}

template<typename T>
inline void read(T& num) {
    char digit = nc();
    num = 0;
    bool negtive = false;

    for (; !isdigit(digit); digit = nc())
        negtive ^= !(digit ^ 45);

    for (; isdigit(digit); digit = nc())
        num = num * 10 + digit - '0';
}

int main() {
    int A, B;
    read(A); read(B);
    std::cout << A + B << '\n';
}