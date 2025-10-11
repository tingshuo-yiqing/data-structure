#include "list.h"
#include "memmgr.h"
#include <assert.h>
#include <stdio.h>

int main() {
    int nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t numsSize = sizeof(nums) / sizeof(nums[0]);
    LinkedList* list = arrayToList(nums, numsSize);
    printf("=======单链表的右旋=======\n");
    printList(list);
    rotateRightList(list, 129);
    printList(list);
    
    printf("=======单链表的归并排序=======\n");
    list = sortList(list);
    printList(list);
    
    printf("=======单链表的反转=======\n");
    reverseList(list);
    printList(list);
    
    

    XFREE(list);
    return 0;
}
