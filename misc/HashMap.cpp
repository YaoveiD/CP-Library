#include <ctime>
#include <iostream>
#include <map>
#include <unordered_map>
#include <chrono>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;

// runs much faster especially on codeforces, but solwer on my PC, why?
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

template <typename K, typename V, typename Hash = custom_hash>
using hash_map = __gnu_pbds::gp_hash_table<K, V, Hash>;
 
template <typename K, typename Hash = custom_hash>
using hash_set = hash_map<K, __gnu_pbds::null_type, Hash>;

const int N = 200005;

void safe_insert(long long x) {
    clock_t begin = clock();
    unordered_map<long long, int, custom_hash> numbers;

    for (int i = 1; i <= N; i++)
        numbers[i * x] = i;

    long long sum = 0;

    for (auto &entry : numbers)
        sum += (entry.first / x) * entry.second;

    printf("x = %lld: %.3lf seconds, sum = %lld\n", x, (double) (clock() - begin) / CLOCKS_PER_SEC, sum);

}

void insert_numbers(long long x) {
    clock_t begin = clock();
    unordered_map<long long, int> numbers;

    for (int i = 1; i <= N; i++)
        numbers[i * x] = i;

    long long sum = 0;

    for (auto &entry : numbers)
        sum += (entry.first / x) * entry.second;

    printf("x = %lld: %.3lf seconds, sum = %lld\n", x, (double) (clock() - begin) / CLOCKS_PER_SEC, sum);
}

void log_insert(long long x) {
    clock_t begin = clock();
    map<long long, int> numbers;

    for (int i = 1; i <= N; i++)
        numbers[i * x] = i;

    long long sum = 0;

    for (auto &entry : numbers)
        sum += (entry.first / x) * entry.second;

    printf("x = %lld: %.3lf seconds, sum = %lld\n", x, (double) (clock() - begin) / CLOCKS_PER_SEC, sum);

}

int main() {
    insert_numbers(107897);
    insert_numbers(126271);
    safe_insert(107897);
    safe_insert(126271);
    log_insert(107897);
    log_insert(126271);
}
