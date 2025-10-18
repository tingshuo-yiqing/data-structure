#include "queue.h"
#include "memmgr.h"

queue* initQueue(int capacity) {
    queue* ret = XMALLOC(sizeof(queue));
    ret->data = XMALLOC(sizeof(queue_eletype) * capacity);
    ret->left = 0;
    ret->right = 0;
    return ret;
}


void freeQueue(queue* q) {
    XFREE(q->data);
    q->data = NULL;
    XFREE(q);
    q = NULL;
}


int getQueueSize(queue* q) {
    return q->right - q->left;
}


bool isQueueEmpty(queue* q) {
    return q->left == q->right;
}


void pushQueue(queue* q, queue_eletype val) {
    q->data[q->right++] = val;
}


queue_eletype popQueue(queue* q) {
    return q->data[q->left++];
}


queue_eletype headQueue(queue* q) {
    return q->data[q->left];
}


queue_eletype tailQueue(queue* q) {
    return q->data[q->right - 1];
}

//todo 循环队列设计
// https://leetcode.cn/problems/design-circular-queue/description/

cqueue* initCQueue(int capacity) {
    if (capacity <= 0) return NULL;
    cqueue* ret = XMALLOC(sizeof(cqueue));
    ret->data = XMALLOC(sizeof(cqueue_eletype) * capacity);
    ret->left = 0;
    ret->right = 0;
    ret->capacity = capacity;
    return ret;
}


void freeCQueue(cqueue* cq) {
    XFREE(cq->data);
    cq->data = NULL;
    XFREE(cq);
    cq = NULL;
}


int getCQueueSize(cqueue* cq) {
    return (cq->right - cq->left + cq->capacity) % cq->capacity;
}


bool isCQueueEmpty(cqueue* cq) {
    return cq->left == cq->right;
}


bool isCQueueFull(cqueue* cq) {
    return (cq->right + 1) % cq->capacity == cq->left;
}


bool pushCQueue(cqueue* cq, cqueue_eletype val) {
    if (isCQueueFull(cq)) return false;
    else {
        cq->data[cq->right] = val;
        cq->right = (cq->right + 1) % cq->capacity;
        return true;
    }
}


cqueue_eletype popCQueue(cqueue* cq) {
    if (isCQueueEmpty(cq)) return false;
    else {
        cqueue_eletype ret = cq->data[cq->left];
        cq->left = (cq->left + 1) % cq->capacity;
        return ret; 
    }
}


cqueue_eletype getHeadCQueue(cqueue* cq) {
    if (isCQueueEmpty(cq)) return -1;
    else {
        return cq->data[cq->left];
    }
}


cqueue_eletype getTailCQueue(cqueue* cq) {
    if (isCQueueEmpty(cq)) return -1;
    //! 队尾看 right-1 的位置
    else {
        int last = (cq->right - 1 + cq->capacity) % cq->capacity;
        return cq->data[last];
    }
}

