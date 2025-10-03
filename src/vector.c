#include "vector.h"

#define CAPACITY 4


// 初始化需要分配两个空间
vector* initVector() {
    vector* ret = (vector*)malloc(sizeof(vector));
    ret->size = 0;
    ret->capacity = CAPACITY;
    ret->data = (int*)malloc(CAPACITY * sizeof(int));
    return ret;
}


// 2倍扩容
void resizeVector(vector* vec) {
    if (vec->size >= vec->capacity) {
        int new_capacity = 2 * vec->capacity;
        int* new_data = (int*)malloc(sizeof(int) * new_capacity);

        for (int i = 0; i < vec->size; ++i) {
            new_data[i] = vec->data[i];
        }
        free(vec->data);
        vec->data = new_data;
        vec->capacity = new_capacity; 
    }
}


int getVectorSize(vector* vec) {
    if (vec) {
        return vec->size;
    }
    return -1;
}

int getVectorCapacity(vector* vec) {
    if (vec) {
        return vec->capacity;
    }
    return -1;
}


int getIndexVectorVal(vector* vec, int index) {
    if (index < 0 || index >= vec->size) {
        printf("out of vector range\n");
    }
    return vec->data[index];
}


// O(n)查找顺序表元素
int findVectorVal(vector* vec, int val) {
    for (int i = 0; i < vec->size; ++i) {
        if (vec->data[i] == val) {
            return i;
        }
    }
    return -1;
}


bool isVectorEmpty(vector* vec) {
    return vec->size == 0;
}


// O(n)索引插入
bool insertVectorVal(vector* vec, int index, int val) {
    if (index < 0 || index > vec->size) {
        return false;
    }
    resizeVector(vec);
    for (int i = vec->size; i > index; --i) {
        vec->data[i] = vec->data[i - 1];
    }
    vec->data[index] = val;
    vec->size++;
    return true;
}


// O(1)尾插push_back
void insertTailVectorVal(vector* vec, int val) {
    resizeVector(vec);
    vec->data[vec->size++] = val;
}

// O(n)索引删除
bool deleteVectorVal(vector* vec, int index) {
    if (index < 0 || index >= vec->size) {
        return false;
    }
    for (int i = index; i < vec->size - 1; ++i) {
        vec->data[i] = vec->data[i + 1];
    }
    vec->size--;
    return true;
}


// O(1)尾删pop_back
void deleteTailVectorVal(vector* vec) {
    if (vec->size > 0) {
        vec->size--;
    }
}

