#include "list.h"
#include "memmgr.h"

Node* createNode(list_eletype val) {
    Node* new_node = XMALLOC(sizeof(Node));
    new_node->data = val;
    new_node->next = NULL;
    return new_node;
}


LinkedList* initLinkedList() {
    LinkedList* ret = XMALLOC(sizeof(LinkedList));
    ret->head = ret->tail = NULL;
    ret->length = 0;
    return ret;
}


void freeList(LinkedList* list) {
    Node* cur = list->head;
    while (cur) {
        Node* temp = cur;
        cur = cur->next;
        XFREE(temp);
    }
    XFREE(list);
}


int getListSize(LinkedList* list) {
    return list->length;
}


Node* getTailNode(LinkedList* list) {
    return list->tail;
}


void insertHeadNode(LinkedList* list, list_eletype val) {
    Node* new_node = createNode(val);
    if (!list->head) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        new_node->next = list->head;
        list->head = new_node;
    }
    list->length++;
}


void insertTailNode(LinkedList* list, list_eletype val) {
    Node* new_node = createNode(val);
    if (!list->tail) {
        list->tail = new_node;
        list->head = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->length++;
}


// 返回bool判断有没有插入成功
bool insertIndexNode(LinkedList* list, int index, list_eletype val) {
    if (index < 0 || index > list->length) {
        return false;
    }
    if (index == 0) {
        insertHeadNode(list, val);
        return true;
    }
    Node* cur = list->head;
    for (int i = 0; i < index - 1; ++i) {
        cur = cur->next;
    }
    Node* new_node = createNode(val);
    new_node->next = cur->next;
    cur->next = new_node;
    return true;
}


bool deleteIndexNode(LinkedList* list, int index) {
    if (index < 0 || index >= getListSize(list)) {  // 可以尾插不能尾删
        return false;
    }
    if (index == 0) {
        Node* temp = list->head;
        list->head = list->head->next;
        XFREE(temp);
        return true;
    }
    Node* cur = list->head;
    for (int i = 0; i < index - 1; ++i) {
        cur = cur->next;
    }
    Node* temp = cur->next;
    cur->next = temp->next;
    XFREE(temp);
    return true;
}


Node* findNode(LinkedList* list, list_eletype val) {
    Node* cur = list->head;
    while (cur) {
        if (cur->data == val) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}


LinkedList* copyList(LinkedList* list) {
    LinkedList* ret = initLinkedList();
    Node* cur = list->head;
    while (cur) {
        insertTailNode(ret, cur->data);
        cur = cur->next;
    }
    return ret;
}


void printList(LinkedList* list) {
    Node* cur = list->head;
    while (cur) {
        printf("%d->", cur->data);
        cur = cur->next;
    }
    printf("NULL\n");
}


LinkedList* arrayToList(int arr[], int arrSize) {
    LinkedList* ret = initLinkedList();
    for (int i = 0; i < arrSize; i++) {
        insertTailNode(ret, arr[i]);
    }
    return ret;
}


void reverseList(LinkedList* list) {
    // The situation where no reversal is required
    if (!list || !list->head || !list->head->next) return;
    Node* cur = list->head;
    Node* pre = NULL;
    while (cur) {
        Node* nxt = cur->next;
        cur->next = pre;
        pre = cur;
        cur = nxt;
    }
    Node* temp = list->head;
    list->head = list->tail;
    list->tail = temp;
}



LinkedList* mergeSortedList(LinkedList* p, LinkedList* q) {
    LinkedList* result = initLinkedList();
    Node dummy;
    Node* tail = &dummy;
    dummy.next = NULL;

    Node* left = p->head;
    Node* right = q->head;

    while (left && right) {
        if (left->data < right->data) {
            tail->next = left;
            left = left->next;
        } else {
            tail->next = right;
            right = right->next;
        }
        tail = tail->next;
        result->length++;
    }

    tail->next = (left ? left : right);

    // Update the tail pointer
    while (tail->next) {
        tail = tail->next;
        result->length++;
    }

    result->head = dummy.next;
    result->tail = tail;

    return result;
}


LinkedList* sortList(LinkedList* list) {
    if (!list || !list->head || !list->head->next) {
        return list;
    }

    Node* slow = list->head;
    Node* fast = list->head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node* second = slow->next;
    slow->next = NULL;

    LinkedList* left = initLinkedList();
    left->head = list->head;
    left->tail = slow;
    left->length = 0;
    Node* temp = left->head;
    while (temp) {
        left->length++;
        temp = temp->next;
    }

    LinkedList* right = initLinkedList();
    right->head = second;
    right->tail = list->tail;
    right->length = 0;
    temp = right->head;
    while (temp) {
        right->length++;
        temp = temp->next;
    }

    LinkedList* sortedLeft = sortList(left);
    LinkedList* sortedRight = sortList(right);

    return mergeSortedList(sortedLeft, sortedRight);
}


bool isCycleList(LinkedList* list) {
    Node* fast = list->head;
    Node* slow = list->head;
    while (fast && fast->next) {
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow) return true;
    }
    return false;
}


void rotateRightList(LinkedList* list, int k) {
    if (!list || !list->head) return;
    k %= list->length;
    
    Node* knode = list->head;
    for (int i = 0; i < list->length - k - 1; ++i) {
        knode = knode->next;
    }

    // rotate
    list->tail->next = list->head;
    list->head = knode->next;
    knode->next = NULL;
    list->tail = knode;
}