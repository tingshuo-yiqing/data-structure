#include "queue.h"

int main() {
    queue* que = initQueue();

    printf("======普通队列=====\n\n");
    if (isQueueEmpty(que)) {
        printf("队列为空\n");
    } else {
        printf("队列大小为%d\n", getQueueSize(que));
    }
    
    int nums[] = {10, -1, 3, 0, 23};
    for (size_t i = 0; i < sizeof(nums) / sizeof(int); ++i) {
        pushQueue(que, nums[i]);
    }
    
    if (isQueueEmpty(que)) {
        printf("队列为空\n");
    } else {
        printf("队列大小为%d\n", getQueueSize(que));
    }
    
    while (!isQueueEmpty(que)) {
        printf("队头%d 队尾%d\n", popQueue(que), tailQueue(que));
    }
    
    
    printf("======循环队列=====\n\n");

    cqueue* cque = initCQueue(3);
    
    int test[4] = {1, 2, 3, 4};
    
    for (int i = 0; i < 4; ++i) {
        if (isCQueueFull(cque)) {
            printf("队列已满\n");
        } else {
            enCQueue(cque, test[i]);
            printf("成功插入%d\n", test[i]);
        }
    }

    // 释放所有分配的内存
    freeQueue(que);
    freeCQueue(cque);

    return 0;
}
