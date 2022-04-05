#include <bits/stdc++.h>
using namespace std;

// verification: https://www.luogu.com.cn/problem/P2602
// source: https://zhuanlan.zhihu.com/p/348851463

const int MAXD = 13;

int64_t dp[MAXD][MAXD];
int digits[MAXD];
int target;

// count from the most significant digit index
int64_t dfs(int index, int count, bool leading, bool tight) {
    int64_t ret = 0;

    if (!index)
        return count;
    
    int64_t &D = dp[index][count];
    
    if (!tight && D != -1 && !leading) // check leading here
        return D;
    
    int most = tight ? digits[index] : 9;

    for (int digit = 0; digit <= most; ++digit) {
        ret += dfs(index - 1, count + (target == 0 ? digit == 0 && !leading : digit == target), 
            leading && digit == 0, tight && digit == most);
    }

    if (!tight && !leading) // check leading here
        D = ret;
    
    return ret;
}

int64_t solve(int64_t x) {
    int len = 0;

    while (x)
        digits[++len] = x % 10, x /= 10;
    
    int64_t ans = dfs(len, 0, true, true);
    return ans;
}

// [L, R]
int64_t solve(int64_t L, int64_t R) {
    return solve(R) - solve(L - 1);
}

int main() {
    int64_t A, B;
    cin >> A >> B;

    for (int i = 0; i <= 9; ++i) {
        memset(dp, -1, sizeof(dp));
        target = i;
        
        if (i > 0)
            cout << ' ';
        cout << solve(A, B);
    }

    cout << '\n';
}
