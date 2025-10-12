#ifndef HEAP
#define HEAP

#include<stdbool.h>
#include<stddef.h>

#define heap_eletype int
#define HEAP_CAPACITY 16

typedef bool (*HeapCmpFunc)(heap_eletype a, heap_eletype b);

typedef struct {
    int* data;
    size_t size;
    size_t capacity;
    HeapCmpFunc cmp;
} Heap;


/**
 * @file heap.h
 * @brief Binary heap implementation with function pointers for min/max heap conversion
 */

/**
 * @brief Initialize a heap with a custom comparison function
 * 
 * @param cmp Comparison function that defines heap ordering
 * @return Heap* Pointer to the newly created heap
 * @note The comparison function should return true if the first argument should be
 *       placed closer to the root than the second argument
 */
Heap* initHeap(HeapCmpFunc cmp);

/**
 * @brief Initialize a min heap (smallest element at root)
 * 
 * @return Heap* Pointer to the newly created min heap
 */
Heap* initMinHeap(void);

/**
 * @brief Initialize a max heap (largest element at root)
 * 
 * @return Heap* Pointer to the newly created max heap
 */
Heap* initMaxHeap(void);

/**
 * @brief Free all memory associated with a heap
 * 
 * @param h Pointer to the heap to free
 */
void freeHeap(Heap* h);

/**
 * @brief Insert a new element into the heap
 * 
 * @param h Pointer to the heap
 * @param val Value to insert
 */
void insertHeap(Heap* h, heap_eletype val);

/**
 * @brief Remove and return the root element from the heap
 * 
 * @param h Pointer to the heap
 * @return heap_eletype The root element
 * @warning Calling this on an empty heap will cause an assertion failure
 */
heap_eletype popHeap(Heap* h);

/**
 * @brief Get the root element without removing it
 * 
 * @param h Pointer to the heap
 * @return heap_eletype The root element
 * @warning Calling this on an empty heap will cause an assertion failure
 */
heap_eletype topHeap(const Heap* h);

/**
 * @brief Check if the heap is empty
 * 
 * @param h Pointer to the heap
 * @return true Heap is empty
 * @return false Heap is not empty
 */
bool isHeapEmpty(const Heap* h);

/**
 * @brief Get the number of elements in the heap
 * 
 * @param h Pointer to the heap
 * @return size_t Number of elements in the heap
 */
size_t getHeapSize(const Heap* h);

/**
 * @brief Print all elements in the heap (for debugging)
 * 
 * @param h Pointer to the heap
 * @note This function prints elements in their array order, not heap order
 */
void printHeap(const Heap* h);

#endif
