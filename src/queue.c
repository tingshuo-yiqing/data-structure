#include "queue.h"

#define CAPACITY 200010

queue* initQueue() {
    queue* ret = (queue*)malloc(sizeof(queue));
    ret->data = (queue_eletype*)malloc(sizeof(queue_eletype) * CAPACITY);
    ret->left = 0;
    ret->right = 0;
    return ret;
}


void freeQueue(queue* que) {
    free(que->data);
    que->data = NULL;
    free(que);
    que = NULL;
}


int getQueueSize(queue* que) {
    return que->right - que->left;
}


bool isQueueEmpty(queue* que) {
    return que->left == que->right;
}


void pushQueue(queue* que, queue_eletype val) {
    que->data[que->right++] = val;
}

queue_eletype popQueue(queue* que) {
    return que->data[que->left++];
}


queue_eletype headQueue(queue* que) {
    return que->data[que->left];
}


queue_eletype tailQueue(queue* que) {
    return que->data[que->right - 1];
}

//todo 循环队列设计
// https://leetcode.cn/problems/design-circular-queue/description/

cqueue* initCQueue(int k) {
    if (k <= 0) return NULL;
    cqueue* ret = (cqueue*)malloc(sizeof(cqueue));
    ret->data = (cqueue_eletype*)malloc(sizeof(cqueue_eletype) * k);
    ret->left = 0;
    ret->right = 0;
    ret->size = 0;
    ret->limit = k;
    return ret;
}


void freeCQueue(cqueue* cque) {
    free(cque->data);
    cque->data = NULL;
    free(cque);
    cque = NULL;
}


int getCQueueSize(cqueue* cque) {
    return cque->size;
}


bool isCQueueEmpty(cqueue* cque) {
    return cque->size == 0;
}


bool isCQueueFull(cqueue* cque) {
    return cque->size == cque->limit;
}


bool enCQueue(cqueue* cque, cqueue_eletype val) {
    if (isCQueueFull(cque)) return false;
    else {
        cque->data[cque->right] = val;
        cque->right = (cque->right == cque->limit - 1 ? 0 : cque->right + 1);
        cque->size++;
        return true;
    }
}


bool deCQueue(cqueue* cque) {
    if (isCQueueEmpty(cque)) return false;
    else {
        cque->left = (cque->left == cque->limit - 1 ? 0 : cque->left + 1);
        cque->size--;
        return true; 
    }
}


cqueue_eletype getHeadCQueue(cqueue* cque) {
    if (isCQueueEmpty(cque)) return -1;
    else {
        return cque->data[cque->left];
    }
}


cqueue_eletype getTailCQueue(cqueue* cque) {
    if (isCQueueEmpty(cque)) return -1;
    //! 队尾看 right-1 的位置
    else {
        int last = (cque->right == 0 ? cque->limit - 1 : cque->right - 1);
        return cque->data[last];
    }
}
