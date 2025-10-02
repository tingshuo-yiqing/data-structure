#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

int cmp(const void* p1, const void* p2) {
    
    int x = *(int*)p1;
    int y = *(int*)p2;
    
    if ((x % 2) != (y % 2)) {
        return (y % 2) - (x % 2);
    }

    return x - y;
}

int main() {
    int nums[] = {10, -1, 0, 99, -100, 13, 19};
    
    int size = sizeof(nums) / sizeof(nums[0]);

    qsort(nums, size, sizeof(int), cmp);

    for (int i = 0; i < size; ++i) {
        printf("%d ", nums[i]);
        if (i == size - 1) printf("\n");
    }

    return 0;
}