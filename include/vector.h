#ifndef DATASTRUCT_VECTOR
#define DATASTRUCT_VECTOR

#ifdef __cplusplus
extern "C" {
#endif

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct vector {
    int size;
    int *data;
    int capacity;
} vector;

vector* initVector();

void resizeVector(vector* vec);

bool isVectorEmpty(vector* vec);

int getVectorSize(vector* vec);

int getVectorCapacity(vector* vec);

int getIndexVectorVal(vector* vec, int index);

int findVectorVal(vector* vec, int val);

bool insertVectorVal(vector* vec, int index, int val);

void insertTailVectorVal(vector* vec, int val);

bool deleteVectorVal(vector* vec, int index);

void deleteTailVectorVal(vector* vec);

#ifdef __cplusplus
}
#endif

#endif
