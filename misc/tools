#include <bits/stdc++.h>

using namespace std;

// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
template<class Fun> class y_combinator_result {
  Fun fun_;
public:
  template<class T> explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
  template<class ...Args> decltype(auto) operator()(Args &&...args) { return fun_(std::ref(*this), std::forward<Args>(args)...); }
};
template<class Fun> decltype(auto) y_combinator(Fun &&fun) { return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun)); }

int main() {
    auto gcd = y_combinator([&](auto gcd, int a, int b) -> int {
        return b == 0 ? a : gcd(b, a % b);
    });
    cout << gcd(4, 6) << '\n';

    cout << y_combinator([&](auto gcd, int a, int b) -> int {
        return b == 0 ? 0 : gcd(b, a % b);
    })(4, 6) << '\n';

    auto GCD = [](auto& self, int a, int b) -> int {
        return b == 0 ? a : self(self, b, a % b);
    };
    cout << GCD(GCD, 4, 6) << '\n'; 

    auto func = y_combinator([&](auto func, int n) -> void {
        if (n < 0) {
            cout << "HAHA" << '\n';
            return;
        }
        func(n - 1);
    });

    func(10);

    return 0;
}