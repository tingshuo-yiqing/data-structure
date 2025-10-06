#ifndef MEMMGR_H
#define MEMMGR_H

#include <stdlib.h>
#include <stdio.h>

//todo: Memory Allocation Validation

void* xmalloc_debug(size_t size, const char* file, int line);
void  xfree_debug(void* ptr, const char* file, int line);


#define XMALLOC(size) xmalloc_debug(size, __FILE__, __LINE__)
#define XFREE(ptr) do { \
    xfree_debug(ptr, __FILE__, __LINE__); \
    (ptr) = NULL; \
} while(0)

#endif
