#include<stdio.h>
#include "heap.h"
#include "memmgr.h"


int main() {
    Heap* h = initHeap();

    // int nums[] = {5, 3, 8, 1, 2, 9};
    int nums[] = {1, 2, 3, 4};
    size_t numsSize = sizeof(nums) / sizeof(nums[0]);
    for (size_t i = 0; i < numsSize; ++i)
        insertHeap(h, nums[i]);

    printf("Heap content: ");
    printHeap(h);

    printf("Top = %d\n", topHeap(h));

    printf("Pop sequence: ");
    while (!isHeapEmpty(h)) {
        printf("%d ", popHeap(h));
    }
    printf("\n");

    freeHeap(h);
    return 0;
}

