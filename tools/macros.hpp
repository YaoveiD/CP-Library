// #pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math,inline")

#define GET_MACRO(_1,_2,_3,NAME,...) NAME
#define FOR3(i,a,b) for(int i=a; i<(b); ++i)
#define FOR2(i,n) for(int i=0; i<(n); ++i)
#define FOR(...) GET_MACRO(__VA_ARGS__, FOR3, FOR2)(__VA_ARGS__)
