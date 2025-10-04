#ifndef DATASTRUCT_QUEUE
#define DATASTRUCT_QUEUE

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

typedef int eletype;

typedef struct queue {
    eletype* data;
    int left;
    int right;
} queue;

queue* initQueue();

void freeQueue(queue* que);

int getQueueSize(queue* que);

bool isQueueEmpty(queue* que);

void pushQueue(queue* que, eletype val);

eletype popQueue(queue* que);

eletype headQueue(queue* que);

eletype tailQueue(queue* que);


typedef struct cqueue {
    eletype* data;
    int left;
    int right;
    int size;
    int limit;
} cqueue;

cqueue* initCQueue(int k);

void freeCQueue(cqueue* cque);

int getCQueueSize(cqueue* cque);

bool isCQueueEmpty(cqueue* cque);

bool isCQueueFull(cqueue* cque);

bool enCQueue(cqueue* cque, eletype val);

bool deCQueue(cqueue* cque);

eletype getHeadCQueue(cqueue* cque);

eletype getTailCQueue(cqueue* cque);

#endif