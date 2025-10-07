// 头文件保护宏
#ifndef DATASTRUCT_LIST
#define DATASTRUCT_LIST 

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 节点定义
typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int val);

void freeList(Node* head);

int getListSize(Node* head);

Node* getTailNode(Node* head);

void insertHeadNode(Node** head, int val);

void insertTailNode(Node** head, int val);

bool insertIndexNode(Node** head, int index, int val);

bool deleteIndexNode(Node** head, int index);

Node* findNode(Node** head, int val);

Node* copyList(Node* head);

void printList(Node* head);

Node* arrayToList(int arr[], int n);

void reverseList(Node** head);

Node* mergeSortedList(Node* left, Node* right);

Node* sortList(Node* head);

#ifdef __cplusplus
}
#endif

#endif
