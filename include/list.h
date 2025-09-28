#ifndef LIST_H
#define LIST_H

// 节点定义
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 链表操作函数
Node* createList();              // 创建空链表
void insertNode(Node** head, int value); // 头插法
void printList(Node* head);      // 打印链表
void freeList(Node* head);       // 释放内存

#endif
