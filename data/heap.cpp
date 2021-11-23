#include <stdio.h>
#include <string.h>

#define SIZE 123456
#define compare(a, b) a > b

typedef int value_t;

value_t heap[SIZE];
int heap_size;

void swim(int node) {
    for (int i = node; i > 1 && compare(heap[node], heap[node / 2]); i /= 2) {
        value_t tt = heap[node];
        heap[node] = heap[node / 2];
        heap[node / 2] = tt;
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

void build(value_t* initial, int start, int end) {
    heap_size = end - start;
    memcpy(heap + 1, initial + start, sizeof(value_t) * heap_size);

    for (int i = heap_size / 2; i > 0; --i)
        sink(i);
}

int main() {
}