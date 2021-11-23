#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <vector>

using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '['; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << ']'; }
 
void debug_out() { cerr << endl; }
template<typename Head, typename... Tail> void debug_out(Head H, Tail... T) { cerr << ' ' << H; debug_out(T...); }
#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 
#endif

auto random_address = [] { char *p = new char; delete p; return uint64_t(p); };
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1));
#define UID(L, R) uniform_int_distribution<int>(L, R)(rng)
#define URD uniform_real_distribution<double>(0.0, 1.0)(rng)

template<typename T> struct min_heap {
    vector<T> heap;
    int heap_size;

    min_heap() : heap_size(0) {
        heap.emplace_back();
    }

    void push(const T& value) {
        heap_size++;

        if (heap_size < int(heap.size()))
            heap[heap_size] = value;
        else
            heap.push_back(value);

        swim(heap_size);
    }

    const T& top() const {
        return heap[1];
    }

    int size() const {
        return heap_size;
    }

    bool empty() const {
        return heap_size == 0;
    } 

    void pop() {
        swap(heap[1], heap[heap_size--]);
        sink(1);
    }

    void build(vector<T>& initial, int start, int end) {
        heap_size = end - start;
        copy(initial.begin() + start, initial.begin() + end, heap.beign() + 1);

        for (int i = heap_size / 2; i > 0; --i)
            sink(i);
    }
private:
    void swim(int node) {
        for (int i = node; i > 1 && heap[i] < heap[i / 2]; i /= 2)
            swap(heap[i], heap[i / 2]);
    }

    int get_child(int node) const {
        return node * 2 + (node * 2 + 1 <= heap_size && heap[node * 2 + 1] < heap[node * 2]);
    }

    void sink(int node) {
        for (int i = node, c = get_child(i); c <= heap_size && heap[c] < heap[i];
            i = c, c = get_child(c))
            swap(heap[c], heap[i]);
    }
};

int main() {
    ios::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(0);
#endif

    int N = 100;
    min_heap<int> mheap;
    priority_queue<int, vector<int>, greater<int>> pq;

    for (int i = 0; i < N; ++i) {
        int op = UID(0, 2);
        assert(mheap.size() == int(pq.size()));

        if (op == 0) {
            int value = rng();
            mheap.push(value);
            pq.push(value);
        } else if (op == 1 && pq.size()) {
            pq.pop();
            mheap.pop();
        }

        if (pq.size())
            assert(mheap.top() == pq.top());
    }
}
