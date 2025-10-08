#ifndef DATASTRUCT_QUEUE
#define DATASTRUCT_QUEUE

#ifdef __cplusplus
extern "C" {
#endif

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include <limits.h>

typedef struct TreeNode TreeNode;  // 前向声明
#define queue_eletype TreeNode*

typedef struct queue {
    queue_eletype* data;
    int left;
    int right;
} queue;

/** 
 * @brief Initialize a queue
 * @return Initialized queue pointer
 */
queue* initQueue();

/**
 * @brief Free the memory occupied by the queue
 * @param que Queue pointer to free
 */
void freeQueue(queue* que);

/**
 * @brief Get the current size of the queue
 * @param que Queue pointer
 * @return Number of elements in the queue
 */
int getQueueSize(queue* que);

/**
 * @brief Check if the queue is empty
 * @param que Queue pointer
 * @return true if the queue is empty, false otherwise
 */
bool isQueueEmpty(queue* que);

/**
 * @brief Add an element to the queue
 * @param que Queue pointer
 * @param val Element to add
 */
void pushQueue(queue* que, queue_eletype val);

/**
 * @brief Remove and return the front element from the queue
 * @param que Queue pointer
 * @return Front element of the queue
 */
queue_eletype popQueue(queue* que);

/**
 * @brief Get the front element without removing it
 * @param que Queue pointer
 * @return Front element of the queue
 */
queue_eletype headQueue(queue* que);

/**
 * @brief Get the rear element without removing it
 * @param que Queue pointer
 * @return Rear element of the queue
 */
queue_eletype tailQueue(queue* que);


#define cqueue_eletype int

typedef struct cqueue {
    cqueue_eletype* data;
    int left;
    int right;
    int size;
    int limit;
} cqueue;

/**
 * @brief Initialize a circular queue with fixed size
 * @param k Capacity of the circular queue
 * @return Initialized circular queue pointer
 */
cqueue* initCQueue(int k);

/**
 * @brief Free the memory occupied by the circular queue
 * @param cque Circular queue pointer to free
 */
void freeCQueue(cqueue* cque);

/**
 * @brief Get the current size of the circular queue
 * @param cque Circular queue pointer
 * @return Number of elements in the circular queue
 */
int getCQueueSize(cqueue* cque);

/**
 * @brief Check if the circular queue is empty
 * @param cque Circular queue pointer
 * @return true if the circular queue is empty, false otherwise
 */
bool isCQueueEmpty(cqueue* cque);

/**
 * @brief Check if the circular queue is full
 * @param cque Circular queue pointer
 * @return true if the circular queue is full, false otherwise
 */
bool isCQueueFull(cqueue* cque);

/**
 * @brief Add an element to the circular queue
 * @param cque Circular queue pointer
 * @param val Element to add
 * @return true if the element was added successfully, false otherwise
 */
bool enCQueue(cqueue* cque, cqueue_eletype val);

/**
 * @brief Remove the front element from the circular queue
 * @param cque Circular queue pointer
 * @return true if the element was removed successfully, false otherwise
 */
bool deCQueue(cqueue* cque);

/**
 * @brief Get the front element of the circular queue without removing it
 * @param cque Circular queue pointer
 * @return Front element of the circular queue
 */
cqueue_eletype getHeadCQueue(cqueue* cque);

/**
 * @brief Get the rear element of the circular queue without removing it
 * @param cque Circular queue pointer
 * @return Rear element of the circular queue
 */
cqueue_eletype getTailCQueue(cqueue* cque);

#ifdef __cplusplus
}
#endif

#endif
