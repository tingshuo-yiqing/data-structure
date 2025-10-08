# 链表模块文档

## 概述

链表模块提供了一个完整的单链表实现，支持常见的链表操作，包括创建、插入、删除、查找、排序等操作。

## 数据结构

### 节点结构体 (Node)

```c
typedef struct Node {
    int data;           // 节点存储的数据
    struct Node* next;  // 指向下一个节点的指针
} Node;
```

## API 函数

### 基础操作

#### `Node* createNode(int val)`
- **功能**: 创建一个新的链表节点
- **参数**: 
  - `val`: 节点存储的整数值
- **返回值**: 指向新创建节点的指针
- **时间复杂度**: O(1)

#### `void freeList(Node* head)`
- **功能**: 释放整个链表的内存
- **参数**: 
  - `head`: 链表的头节点指针
- **时间复杂度**: O(n)

#### `int getListSize(Node* head)`
- **功能**: 获取链表的长度
- **参数**: 
  - `head`: 链表的头节点指针
- **返回值**: 链表的节点数量
- **时间复杂度**: O(n)

#### `Node* getTailNode(Node* head)`
- **功能**: 获取链表的尾节点
- **参数**: 
  - `head`: 链表的头节点指针
- **返回值**: 指向尾节点的指针
- **时间复杂度**: O(n)

### 插入操作

#### `void insertHeadNode(Node** head, int val)`
- **功能**: 在链表头部插入新节点
- **参数**: 
  - `head`: 指向头节点指针的指针（允许修改头指针）
  - `val`: 要插入的值
- **时间复杂度**: O(1)

#### `void insertTailNode(Node** head, int val)`
- **功能**: 在链表尾部插入新节点
- **参数**: 
  - `head`: 指向头节点指针的指针
  - `val`: 要插入的值
- **时间复杂度**: O(n)

#### `bool insertIndexNode(Node** head, int index, int val)`
- **功能**: 在指定索引位置插入新节点
- **参数**: 
  - `head`: 指向头节点指针的指针
  - `index`: 插入位置的索引（0-based）
  - `val`: 要插入的值
- **返回值**: 插入成功返回true，失败返回false
- **时间复杂度**: O(n)

### 删除操作

#### `bool deleteIndexNode(Node** head, int index)`
- **功能**: 删除指定索引位置的节点
- **参数**: 
  - `head`: 指向头节点指针的指针
  - `index`: 要删除节点的索引（0-based）
- **返回值**: 删除成功返回true，失败返回false
- **时间复杂度**: O(n)

### 查找操作

#### `Node* findNode(Node** head, int val)`
- **功能**: 在链表中查找包含指定值的节点
- **参数**: 
  - `head`: 指向头节点指针的指针
  - `val`: 要查找的值
- **返回值**: 找到的节点指针，未找到返回NULL
- **时间复杂度**: O(n)

### 复制操作

#### `Node* copyList(Node* head)`
- **功能**: 复制整个链表
- **参数**: 
  - `head`: 要复制的链表头节点
- **返回值**: 新链表的头节点指针
- **时间复杂度**: O(n)

### 输出操作

#### `void printList(Node* head)`
- **功能**: 打印链表内容
- **参数**: 
  - `head`: 链表的头节点指针
- **输出格式**: `1->2->3->NULL`
- **时间复杂度**: O(n)

### 转换操作

#### `Node* arrayToList(int arr[], int n)`
- **功能**: 将数组转换为链表
- **参数**: 
  - `arr`: 整型数组
  - `n`: 数组长度
- **返回值**: 链表的头节点指针
- **时间复杂度**: O(n)

### 排序和反转操作

#### `void reverseList(Node** head)`
- **功能**: 反转链表
- **参数**: 
  - `head`: 指向头节点指针的指针
- **时间复杂度**: O(n)

#### `Node* mergeSortedList(Node* left, Node* right)`
- **功能**: 合并两个有序链表
- **参数**: 
  - `left`: 第一个有序链表的头节点
  - `right`: 第二个有序链表的头节点
- **返回值**: 合并后的有序链表头节点
- **时间复杂度**: O(n+m)

#### `Node* sortList(Node* head)`
- **功能**: 对链表进行排序（使用归并排序算法）
- **参数**: 
  - `head`: 要排序的链表头节点
- **返回值**: 排序后的链表头节点
- **时间复杂度**: O(n log n)

## 使用示例

```c
#include "list.h"

int main() {
    // 创建链表
    Node* head = NULL;
    
    // 插入操作
    insertHeadNode(&head, 1);
    insertTailNode(&head, 3);
    insertIndexNode(&head, 1, 2);
    
    // 打印链表: 1->2->3->NULL
    printList(head);
    
    // 反转链表
    reverseList(&head);
    printList(head);  // 3->2->1->NULL
    
    // 排序链表
    head = sortList(head);
    printList(head);  // 1->2->3->NULL
    
    // 释放内存
    freeList(head);
    
    return 0;
}
```

## 注意事项

1. 所有修改链表头指针的函数都使用双重指针 `Node**` 参数
2. 内存管理使用自定义的 `XMALLOC` 和 `XFREE` 宏
3. 索引操作会进行边界检查
4. 链表节点存储的数据类型为 `int`
5. 排序算法使用归并排序，时间复杂度为 O(n log n)

## 依赖关系

- 依赖于 `memmgr.h` 中的内存管理函数
- 使用标准库 `stdio.h`, `stdlib.h`, `stdbool.h`
