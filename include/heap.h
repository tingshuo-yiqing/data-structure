#ifndef HEAP
#define HEAP

#include<stdbool.h>
#include<stddef.h>

#define heap_eletype int
#define HEAP_CAPACITY 100

typedef struct {
    int* data;
    size_t size;
    size_t capacity;
} Heap;


Heap* initHeap();

void freeHeap(Heap* h);

void insertHeap(Heap* h, heap_eletype val);

heap_eletype popHeap(Heap* h);

heap_eletype topHeap(const Heap* h);

bool isHeapEmpty(Heap* h);

size_t getHeapSize(Heap* h);

void printHeap(Heap* h);
#endif