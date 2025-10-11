// 头文件保护宏
#ifndef DATASTRUCT_LIST
#define DATASTRUCT_LIST 

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#define list_eletype int


// 节点定义
typedef struct Node {
    list_eletype data;
    struct Node* next;
} Node;

typedef struct LinkedList {
    Node* head;
    Node* tail;
    int length;
} LinkedList;

Node* createNode(list_eletype val);

LinkedList* initLinkedList();

void freeList(LinkedList* list);

int getListSize(LinkedList* list);

Node* getTailNode(LinkedList* list);

void insertHeadNode(LinkedList* list, list_eletype val);

void insertTailNode(LinkedList* list, list_eletype val);

bool insertIndexNode(LinkedList* list, int index, list_eletype val);

bool deleteIndexNode(LinkedList* list, int index);

Node* findNode(LinkedList* list, list_eletype val);

LinkedList* copyList(LinkedList* list);

void printList(LinkedList* list);

LinkedList* arrayToList(int arr[], int arrSize);

void reverseList(LinkedList* list);

LinkedList* mergeSortedList(LinkedList* p, LinkedList* q);

LinkedList* sortList(LinkedList* list);

bool isCycleList(LinkedList* list);

void rotateRightList(LinkedList* list, int k);

#ifdef __cplusplus
}
#endif

#endif
