#ifndef DATASTRUCT_VECTOR
#define DATASTRUCT_VECTOR

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdio.h>

#define CAPACITY 16
#define vector_eletype int

typedef struct vector {
    int size;
    int *data;
    int capacity;
} vector;

/**
 * @brief Initialize a vector with default capacity
 * @return Pointer to the initialized vector
 */
vector* initVector();

/**
 * @brief Resize the vector when capacity is reached (2x expansion)
 * @param vec Vector to resize
 */
void resizeVector(vector* vec);

/**
 * @brief Check if the vector is empty
 * @param vec Vector to check
 * @return true if vector is empty, false otherwise
 */
bool isVectorEmpty(vector* vec);

/**
 * @brief Get the current size of the vector
 * @param vec Vector to check
 * @return Size of the vector, or -1 if vector is NULL
 */
int getVectorSize(vector* vec);

/**
 * @brief Get the current capacity of the vector
 * @param vec Vector to check
 * @return Capacity of the vector, or -1 if vector is NULL
 */
int getVectorCapacity(vector* vec);

/**
 * @brief Get the value at specified index
 * @param vec Vector to access
 * @param index Index to retrieve
 * @return Value at the specified index
 * @note Prints error message if index is out of range
 */
vector_eletype getIndexVectorVal(vector* vec, int index);

/**
 * @brief Find the first occurrence of a value in the vector
 * @param vec Vector to search
 * @param val Value to find
 * @return Index of the value if found, -1 otherwise
 */
int findVectorVal(vector* vec, vector_eletype val);

/**
 * @brief Insert a value at specified index
 * @param vec Vector to modify
 * @param index Index to insert at
 * @param val Value to insert
 * @return true if insertion successful, false if index is invalid
 */
bool insertVectorVal(vector* vec, int index, vector_eletype val);

/**
 * @brief Insert a value at the end of the vector (push_back)
 * @param vec Vector to modify
 * @param val Value to insert
 */
void insertTailVectorVal(vector* vec, vector_eletype val);

/**
 * @brief Delete the value at specified index
 * @param vec Vector to modify
 * @param index Index to delete
 * @return true if deletion successful, false if index is invalid
 */
bool deleteVectorVal(vector* vec, int index);

/**
 * @brief Delete the value at the end of the vector (pop_back)
 * @param vec Vector to modify
 */
void deleteTailVectorVal(vector* vec);

#ifdef __cplusplus
}
#endif

#endif
