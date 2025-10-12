#ifndef MEMMGR_H
#define MEMMGR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>

//todo: Memory Allocation Validation

void* xmalloc_debug(size_t size, const char* file, int line);

void* xrealloc_debug(void* ptr, size_t size, const char* file, int line);

void  xfree_debug(void* ptr, const char* file, int line);


#define XMALLOC(size) xmalloc_debug(size, __FILE__, __LINE__)

#define XREALLOC(ptr, size) xrealloc_debug(ptr, size, __FILE__, __LINE__)

#define XFREE(ptr) do { \
    xfree_debug(ptr, __FILE__, __LINE__); \
    (ptr) = NULL; \
} while(0)

#ifdef __cplusplus
}
#endif

#endif
