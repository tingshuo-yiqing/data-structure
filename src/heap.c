#include<assert.h>
#include "heap.h"
#include "memmgr.h"
#include "myfunction.h"


/* 初始化和回收接口 */

Heap* initHeap() {
    Heap* ret = XMALLOC(sizeof(Heap));
    heap_eletype* data = XMALLOC(sizeof(heap_eletype) * HEAP_CAPACITY);
    ret->data = data;
    ret->size = 0;
    ret->capacity = HEAP_CAPACITY;
    return ret;
}


void freeHeap(Heap* h) {
    if (h) {
        XFREE(h->data);
        XFREE(h);
    }
}


/* 辅助函数 */

static inline size_t parent(size_t i) { return (i - 1) / 2; }
static inline size_t left(size_t i) { return i * 2 + 1; }
static inline size_t right(size_t i) { return i * 2 + 2; }

// 扩容
static void resize(Heap* h) {
    size_t new_capacity = h->capacity < 1024
        ? h->capacity * 2
        : h->capacity + h->capacity / 2;

    h->data = XREALLOC(h->data, sizeof(heap_eletype) * new_capacity);
    h->capacity = new_capacity;
}

// 上浮
static void heapifyUp(Heap* h, size_t i) {
    while (i > 0 && h->data[i] < h->data[parent(i)]) {
        SWAP(h->data[i], h->data[parent(i)]);
        i = parent(i);
    }
}

// 下沉
static void heapifyDown(Heap* h, size_t i) {
    size_t len = h->size;
    while (left(i) < len) {
        size_t l = left(i);
        size_t r = right(i);
        size_t best = i;

        if (l < len && h->data[l] < h->data[best])
            best = l;
        if (r < len && h->data[r] < h->data[best])
            best = r;
        
        if (best == i) break;
        SWAP(h->data[best], h->data[i]);
        i = best;
    }
}

/* 对外接口 */

void insertHeap(Heap* h, heap_eletype val) {
    if (h->size == h->capacity) resize(h);
    h->data[h->size++] = val;
    heapifyUp(h, h->size - 1);
}

heap_eletype popHeap(Heap* h) {
    heap_eletype ret = h->data[0];
    h->data[0] = h->data[--h->size];
    heapifyDown(h, 0);
    return ret;
}

heap_eletype topHeap(const Heap* h) {
    assert(h->size > 0 && "heap_top on empty heap!");
    return h->data[0];
}

bool isHeapEmpty(Heap* h) {
    return h->size == 0;
}

size_t getHeapSize(Heap* h) {
    return h->size;
}

void printHeap(Heap* h) {
    for (size_t i = 0; i < h->size; ++i) {
        // 占位符根据heap_eleype实际类型调整
        printf("%d ", h->data[i]);
    }
    printf("\n");
}