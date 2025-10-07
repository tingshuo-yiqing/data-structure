#include "list.h"
#include <assert.h>
#include <stdio.h>

// 测试辅助函数：验证链表内容
void verifyList(Node* head, int expected[], int size, const char* testName) {
    printf("测试: %s\n", testName);
    printf("期望: ");
    for (int i = 0; i < size; i++) {
        printf("%d->", expected[i]);
    }
    printf("NULL\n");
    
    printf("实际: ");
    printList(head);
    
    Node* cur = head;
    for (int i = 0; i < size; i++) {
        assert(cur != NULL);
        assert(cur->data == expected[i]);
        cur = cur->next;
    }
    assert(cur == NULL);
    assert(getListSize(head) == size);
    printf("✅ 测试通过\n\n");
}

// 测试1: 基础创建和释放
void testBasicCreation() {
    printf("=== 测试1: 基础创建和释放 ===\n");
    
    Node* head = NULL;
    
    // 测试空链表
    assert(getListSize(head) == 0);
    assert(getTailNode(head) == NULL);
    printf("✅ 空链表测试通过\n");
    
    // 创建单个节点
    head = createNode(42);
    assert(head != NULL);
    assert(head->data == 42);
    assert(head->next == NULL);
    assert(getListSize(head) == 1);
    assert(getTailNode(head) == head);
    printf("✅ 单节点创建测试通过\n");
    
    freeList(head);
    printf("✅ 链表释放测试通过\n\n");
}

// 测试2: 头插法
void testInsertHead() {
    printf("=== 测试2: 头插法 ===\n");
    
    Node* head = NULL;
    
    insertHeadNode(&head, 3);
    insertHeadNode(&head, 2);
    insertHeadNode(&head, 1);
    
    int expected[] = {1, 2, 3};
    verifyList(head, expected, 3, "头插法");
    
    freeList(head);
}

// 测试3: 尾插法
void testInsertTail() {
    printf("=== 测试3: 尾插法 ===\n");
    
    Node* head = NULL;
    
    insertTailNode(&head, 1);
    insertTailNode(&head, 2);
    insertTailNode(&head, 3);
    
    int expected[] = {1, 2, 3};
    verifyList(head, expected, 3, "尾插法");
    
    freeList(head);
}

// 测试4: 按索引插入
void testInsertAtIndex() {
    printf("=== 测试4: 按索引插入 ===\n");
    
    Node* head = NULL;
    
    // 在空链表中插入
    assert(insertIndexNode(&head, 0, 10) == true);
    
    // 在头部插入
    assert(insertIndexNode(&head, 0, 5) == true);
    
    // 在中间插入
    assert(insertIndexNode(&head, 1, 7) == true);
    
    // 在尾部插入
    assert(insertIndexNode(&head, 3, 15) == true);
    
    // 测试无效索引
    assert(insertIndexNode(&head, 10, 20) == false);  // 索引过大
    assert(insertIndexNode(&head, -1, 20) == false);  // 索引为负
    
    int expected[] = {5, 7, 10, 15};
    verifyList(head, expected, 4, "按索引插入");
    
    freeList(head);
}

// 测试5: 按索引删除
void testDeleteAtIndex() {
    printf("=== 测试5: 按索引删除 ===\n");
    
    Node* head = NULL;
    insertTailNode(&head, 1);
    insertTailNode(&head, 2);
    insertTailNode(&head, 3);
    insertTailNode(&head, 4);
    insertTailNode(&head, 5);
    
    // 删除中间节点
    assert(deleteIndexNode(&head, 2) == true);  // 删除3
    int expected1[] = {1, 2, 4, 5};
    verifyList(head, expected1, 4, "删除中间节点");
    
    // 删除头部节点
    assert(deleteIndexNode(&head, 0) == true);  // 删除1
    int expected2[] = {2, 4, 5};
    verifyList(head, expected2, 3, "删除头部节点");
    
    // 删除尾部节点
    assert(deleteIndexNode(&head, 2) == true);  // 删除5
    int expected3[] = {2, 4};
    verifyList(head, expected3, 2, "删除尾部节点");
    
    // 测试无效索引
    assert(deleteIndexNode(&head, 5) == false);  // 索引过大
    assert(deleteIndexNode(&head, -1) == false); // 索引为负
    
    freeList(head);
}

// 测试6: 查找节点
void testFindNode() {
    printf("=== 测试6: 查找节点 ===\n");
    
    Node* head = NULL;
    insertTailNode(&head, 10);
    insertTailNode(&head, 20);
    insertTailNode(&head, 30);
    insertTailNode(&head, 40);
    
    // 查找存在的节点
    Node* found = findNode(&head, 20);
    assert(found != NULL);
    assert(found->data == 20);
    printf("✅ 查找存在的节点测试通过\n");
    
    // 查找不存在的节点
    found = findNode(&head, 99);
    assert(found == NULL);
    printf("✅ 查找不存在的节点测试通过\n");
    
    // 查找头部节点
    found = findNode(&head, 10);
    assert(found != NULL);
    assert(found->data == 10);
    printf("✅ 查找头部节点测试通过\n");
    
    // 查找尾部节点
    found = findNode(&head, 40);
    assert(found != NULL);
    assert(found->data == 40);
    printf("✅ 查找尾部节点测试通过\n");
    
    freeList(head);
}

// 测试7: 链表复制
void testCopyList() {
    printf("=== 测试7: 链表复制 ===\n");
    
    Node* original = NULL;
    insertTailNode(&original, 1);
    insertTailNode(&original, 2);
    insertTailNode(&original, 3);
    
    Node* copy = copyList(original);
    
    // 验证复制内容
    int expected[] = {1, 2, 3};
    verifyList(copy, expected, 3, "链表复制");
    
    // 验证是深拷贝（修改原链表不影响副本）
    deleteIndexNode(&original, 1);  // 删除原链表的第二个节点
    assert(getListSize(original) == 2);
    assert(getListSize(copy) == 3);  // 副本应该保持不变
    
    printf("✅ 深拷贝验证通过\n");
    
    freeList(original);
    freeList(copy);
}

// 测试8: 数组转链表
void testArrayToList() {
    printf("=== 测试8: 数组转链表 ===\n");
    
    int arr[] = {5, 10, 15, 20, 25};
    Node* head = arrayToList(arr, 5);
    
    int expected[] = {5, 10, 15, 20, 25};
    verifyList(head, expected, 5, "数组转链表");
    
    freeList(head);
}

// 测试9: 链表反转
void testReverseList() {
    printf("=== 测试9: 链表反转 ===\n");
    
    Node* head = NULL;
    insertTailNode(&head, 1);
    insertTailNode(&head, 2);
    insertTailNode(&head, 3);
    insertTailNode(&head, 4);
    
    printf("反转前: ");
    printList(head);
    
    reverseList(&head);
    
    int expected[] = {4, 3, 2, 1};
    verifyList(head, expected, 4, "链表反转");
    
    freeList(head);
}

// 测试10: 合并有序链表
void testMergeSortedList() {
    printf("=== 测试10: 合并有序链表 ===\n");
    
    // 创建两个有序链表
    Node* list1 = NULL;
    insertTailNode(&list1, 1);
    insertTailNode(&list1, 3);
    insertTailNode(&list1, 5);
    
    Node* list2 = NULL;
    insertTailNode(&list2, 2);
    insertTailNode(&list2, 4);
    insertTailNode(&list2, 6);
    
    printf("链表1: ");
    printList(list1);
    printf("链表2: ");
    printList(list2);
    
    Node* merged = mergeSortedList(list1, list2);
    
    int expected[] = {1, 2, 3, 4, 5, 6};
    verifyList(merged, expected, 6, "合并有序链表");
    
    freeList(merged);
}

// 测试11: 链表排序
void testSortList() {
    printf("=== 测试11: 链表排序 ===\n");
    
    Node* head = NULL;
    insertTailNode(&head, 5);
    insertTailNode(&head, 2);
    insertTailNode(&head, 8);
    insertTailNode(&head, 1);
    insertTailNode(&head, 9);
    
    printf("排序前: ");
    printList(head);
    
    head = sortList(head);
    
    int expected[] = {1, 2, 5, 8, 9};
    verifyList(head, expected, 5, "链表排序");
    
    freeList(head);
}

// 测试12: 边界情况测试
void testEdgeCases() {
    printf("=== 测试12: 边界情况测试 ===\n");
    
    Node* head = NULL;
    
    // 测试空链表的各种操作
    assert(getListSize(head) == 0);
    assert(getTailNode(head) == NULL);
    assert(findNode(&head, 42) == NULL);
    assert(deleteIndexNode(&head, 0) == false);
    assert(insertIndexNode(&head, 1, 10) == false);  // 在空链表非0位置插入
    
    // 测试单节点链表
    insertHeadNode(&head, 100);
    assert(getListSize(head) == 1);
    assert(getTailNode(head) == head);
    assert(findNode(&head, 100) == head);
    assert(deleteIndexNode(&head, 0) == true);
    assert(head == NULL);
    
    printf("✅ 边界情况测试通过\n\n");
}

// 测试13: 内存管理测试
void testMemoryManagement() {
    printf("=== 测试13: 内存管理测试 ===\n");
    
    // 测试大量节点创建和释放
    Node* head = NULL;
    for (int i = 0; i < 1000; i++) {
        insertTailNode(&head, i);
    }
    assert(getListSize(head) == 1000);
    
    // 测试部分删除
    for (int i = 0; i < 500; i++) {
        assert(deleteIndexNode(&head, 0) == true);
    }
    assert(getListSize(head) == 500);
    
    freeList(head);
    printf("✅ 内存管理测试通过\n\n");
}

int main() {
    printf("🚀 开始全面链表测试\n\n");
    
    testBasicCreation();
    testInsertHead();
    testInsertTail();
    testInsertAtIndex();
    testDeleteAtIndex();
    testFindNode();
    testCopyList();
    testArrayToList();
    testReverseList();
    testMergeSortedList();
    testSortList();
    testEdgeCases();
    testMemoryManagement();
    
    printf("🎉 所有测试通过！链表实现功能完整且正确。\n");
    return 0;
}
