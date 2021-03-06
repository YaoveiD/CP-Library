#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;

#define SIZE 123456
#define INF 1000000008
#define N_MAX 2555

template<typename T> struct min_heap {
    vector<T> heap;
    int heap_size;

    min_heap() : heap_size(0) {
        heap.emplace_back();
    }

    void push(const T& value) {
        heap_size++;

        if (heap_size < int(heap.size())) {
            heap[heap_size] = value;
        } else {
            // Prevent increasing capacity by only 1 each time. Havn't tested.
            heap.reserve(heap_size/16 + heap_size);
            heap.push_back(value);
        }

        swim(heap_size);
    }

    const T& top() const { return heap[1]; }

    int size() const { return heap_size; }

    bool empty() const { return heap_size == 0; } 

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

struct node {
    int to, cost;
    struct node *next;
} *adj[N_MAX];

void add_edge(int a, int b, int c) {
    struct node *n = (struct node*)malloc(sizeof(*n));
    n->to = b;
    n->cost = c;
    n->next = adj[a];
    adj[a] = n;
}

typedef struct dv {
    long long d;
    int node;
} value_t;

value_t heap[SIZE];
int heap_size;

int compare(value_t a, value_t b) {
    return a.d < b.d;
}

void swim(int node) {
    for (int i = node; i > 1 && compare(heap[i], heap[i / 2]); i /= 2) {
        value_t tt = heap[i];
        heap[i] = heap[i / 2];
        heap[i / 2] = tt;
    }
}

int get_child(int node) {
    return node * 2 + (node * 2 + 1 <= heap_size && compare(heap[node * 2 + 1], heap[node * 2]));
}

void sink(int node) {
    for (int i = node, c = get_child(i); c <= heap_size && compare(heap[c], heap[i]);
        i = c, c = get_child(c)) {
        value_t tt = heap[c];
        heap[c] = heap[i];
        heap[i] = tt;
    }
}

void push(value_t value) {
    heap[++heap_size] = value;
    swim(heap_size);
}

value_t top() {
    return heap[1];
}

void pop() {
    value_t tt = heap[1];
    heap[1] = heap[heap_size];
    heap[heap_size--] = tt;
    sink(1);
}

long long dist[N_MAX];
int visited[N_MAX];

int main() {
    int N, M, S, T;
    scanf("%d%d%d%d", &N, &M, &S, &T);
    S--; T--;

    for (int i = 0; i < M; ++i) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a--; b--;
        add_edge(a, b, c);
        add_edge(b, a, c);        
    }

    for (int i = 0; i < N; ++i)
        dist[i] = INF;

    dist[S] = 0;
    struct dv v;
    v.d = 0; v.node = S;
    push(v);

    while (heap_size > 0) {
        int node = top().node;
        pop();

        if (visited[node])
            continue;

        visited[node] = 1;

        for (struct node *n = adj[node]; n; n = n->next)
            if (dist[n->to] > dist[node] + n->cost) {
                dist[n->to] = dist[node] + n->cost;
                v.d = dist[n->to];
                v.node = n->to;
                push(v);
            }
    }

    printf("%lld\n", dist[T]);
}