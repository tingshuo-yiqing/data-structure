#include<assert.h>
#include "heap.h"
#include "memmgr.h"
#include "myfunction.h"

/* Helper function declarations */

static bool minHeapCmp(heap_eletype a, heap_eletype b);
static bool maxHeapCmp(heap_eletype a, heap_eletype b);

/* Initialization and cleanup interfaces */

Heap* initHeap(HeapCmpFunc cmp) {
    assert(cmp != NULL && "Comparison function cannot be NULL!");
    Heap* ret = XMALLOC(sizeof(Heap));
    heap_eletype* data = XMALLOC(sizeof(heap_eletype) * HEAP_CAPACITY);
    ret->data = data;
    ret->size = 0;
    ret->capacity = HEAP_CAPACITY;
    ret->cmp = cmp;
    return ret;
}

Heap* initMinHeap(void) {
    return initHeap(minHeapCmp);
}
Heap* initMaxHeap(void) {
    return initHeap(maxHeapCmp);
}

void freeHeap(Heap* h) {
    XFREE(h->data);
    XFREE(h);
}


/* Helper functions */

// Min heap: parent node < child node
static bool minHeapCmp(heap_eletype a, heap_eletype b) {
    return a < b;
}

// Max heap: parent node > child node
static bool maxHeapCmp(heap_eletype a, heap_eletype b) {
    return a > b;
}

static inline size_t parent(size_t i) { return (i - 1) / 2; }
static inline size_t left(size_t i) { return i * 2 + 1; }
static inline size_t right(size_t i) { return i * 2 + 2; }

// Resize
static void resize(Heap* h) {
    size_t new_capacity = h->capacity < 1024
        ? h->capacity * 2
        : h->capacity + h->capacity / 2;

    h->data = XREALLOC(h->data, sizeof(heap_eletype) * new_capacity);
    h->capacity = new_capacity;
}

// Heapify up
static void heapifyUp(Heap* h, size_t i) {
    while (i > 0 && h->cmp(h->data[i], h->data[parent(i)])) {
        SWAP(h->data[i], h->data[parent(i)]);
        i = parent(i);
    }
}

// Heapify down
static void heapifyDown(Heap* h, size_t i) {
    size_t len = h->size;
    while (left(i) < len) {
        size_t l = left(i);
        size_t r = right(i);
        size_t best = i;

        if (l < len && h->cmp(h->data[l], h->data[best]))
            best = l;
        if (r < len && h->cmp(h->data[r], h->data[best]))
            best = r;
        
        if (best == i) break;
        SWAP(h->data[best], h->data[i]);
        i = best;
    }
}

/* Public interfaces */

void insertHeap(Heap* h, heap_eletype val) {
    if (h->size == h->capacity) resize(h);
    h->data[h->size++] = val;
    heapifyUp(h, h->size - 1);
}

heap_eletype popHeap(Heap* h) {
    assert(h->size > 0 && "heap_pop on empty heap!");
    heap_eletype ret = h->data[0];
    h->data[0] = h->data[--h->size];
    heapifyDown(h, 0);
    return ret;
}

heap_eletype topHeap(const Heap* h) {
    assert(h->size > 0 && "heap_top on empty heap!");
    return h->data[0];
}

bool isHeapEmpty(const Heap* h) {
    return h->size == 0;
}

size_t getHeapSize(const Heap* h) {
    return h->size;
}

void printHeap(const Heap* h) {
    for (size_t i = 0; i < h->size; ++i) {
    // Placeholder should be adjusted based on actual heap_eletype
        printf("%d ", h->data[i]);
    }
    printf("\n");
}
