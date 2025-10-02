#include "list.h"

Node* createNode(int val) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return NULL;
    }
    new_node->data = val;
    new_node->next = NULL;
    return new_node;
}


void freeList(Node* head) {
    Node* cur = head;
    while (cur) {
        Node* temp = cur;
        cur = cur->next;
        free(temp);
        temp = NULL;
    }
}


int getListSize(Node* head) {
    int ret = 0;
    Node* cur = head;
    while (cur) {
        ret++;
        cur = cur->next;
    }
    return ret;
}


Node* getTailNode(Node* head) {
    if (!head) return NULL;
    Node* ret = head;
    while (ret->next) {
        ret = ret->next;
    }
    return ret;
}


// 传入头结点的指针，支持直接在函数内部修改头指针而不是作为返回值
void insertHeadNode(Node** head, int val) {
    Node* new_node = createNode(val);
    if (new_node == NULL) {
        return;
    }
    new_node->next = *head;
    *head = new_node;
}


void insertTailNode(Node** head, int val) {
    Node* new_node = createNode(val);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    Node* tail = getTailNode(*head);
    tail->next = new_node;
}


// 传入头结点的指针，返回bool判断有没有插入成功
bool insertIndexNode(Node** head, int index, int val) {
    if (index < 0 || index > getListSize(*head)) {
        return false;
    }
    if (index == 0) {
        insertHeadNode(head, val);
        return true;
    }
    Node* cur = *head;
    for (int i = 0; i < index - 1; ++i) {
        cur = cur->next;
    }
    Node* new_node = createNode(val);
    if (new_node == NULL) {
        return false;
    }
    new_node->next = cur->next;
    cur->next = new_node;
    return true;
}


bool deleteIndexNode(Node** head, int index) {
    if (index < 0 || index >= getListSize(*head)) {  // 可以尾插不能尾删
        return false;
    }
    if (index == 0) {
        Node* temp = *head;
        *head = (*head)->next;
        free(temp);
        return true;
    }
    Node* cur = *head;
    for (int i = 0; i < index - 1; ++i) {
        cur = cur->next;
    }
    Node* temp = cur->next;
    cur->next = temp->next;
    free(temp);
    return true;
}


Node* findNode(Node** head, int val) {
    Node* cur = *head;
    while (cur) {
        if (cur->data == val) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}


Node* copyList(Node* head) {
    Node* new_head = NULL;
    Node* cur = head;
    while (cur) {
        insertTailNode(&new_head, cur->data);
        cur = cur->next;
    }
    return new_head;
}


void printList(Node* head) {
    Node* cur = head;
    while (cur) {
        printf("%d->", cur->data);
        cur = cur->next;
    }
    printf("NULL\n");
}


Node* arrayToList(int arr[], int n) {
    Node* head = NULL;
    for (int i = 0; i < n; i++) {
        insertTailNode(&head, arr[i]);
    }
    return head;
}



void reverseList(Node** head) {
    Node* cur = *head;
    Node* pre = NULL;
    while (cur) {
        Node* nxt = cur->next;
        cur->next = pre;
        pre = cur;
        cur = nxt;
    }
    *head = pre;
}


// 使用虚拟头结点辅助合并两个有序链表
Node* mergeSortedList(Node* left, Node* right) {
    Node dummy;
    Node* tail = &dummy;
    dummy.next = NULL;

    while (left && right) {
        if (left->data < right->data) {
            tail->next = left;
            left = left->next;
        } else {
            tail->next = right;
            right = right->next;
        }
        tail = tail->next;
    }

    tail->next = (left ? left : right);

    return dummy.next;
}


// 归并排序链表
Node* sortList(Node* head) {
    if (!head || !head->next) {
        return head;
    }
    // 寻找链表中间节点
    Node* slow = head;
    Node* fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    // 将链表一份为二
    Node* second = slow->next;
    slow->next = NULL;
    Node* first = head;
    // 递归合并
    return mergeSortedList(sortList(first), sortList(second));
}

