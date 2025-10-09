#include "vector.h"
#include "memmgr.h"
#include <stdio.h>

vector* initVector() {
    vector* ret = XMALLOC(sizeof(vector));
    ret->size = 0;
    ret->capacity = CAPACITY;
    ret->data = XMALLOC(CAPACITY * sizeof(vector_eletype));
    return ret;
}


void resizeVector(vector* vec) {
    if (vec->size >= vec->capacity) {
        int new_capacity = 2 * vec->capacity;
        vector_eletype* new_data = XMALLOC(sizeof(vector_eletype) * new_capacity);

        for (int i = 0; i < vec->size; ++i) {
            new_data[i] = vec->data[i];
        }
        XFREE(vec->data);
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


vector_eletype getIndexVectorVal(vector* vec, int index) {
    if (index < 0 || index >= vec->size) {
        printf("out of vector range\n");
    }
    return vec->data[index];
}


int findVectorVal(vector* vec, vector_eletype val) {
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


bool insertVectorVal(vector* vec, int index, vector_eletype val) {
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


void insertTailVectorVal(vector* vec, vector_eletype val) {
    resizeVector(vec);
    vec->data[vec->size++] = val;
}


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


void deleteTailVectorVal(vector* vec) {
    if (vec->size > 0) {
        vec->size--;
    }
}
