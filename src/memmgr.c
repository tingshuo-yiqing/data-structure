#include "memmgr.h"

void* xmalloc_debug(size_t size, const char* file, int line) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "[%s:%d] malloc(%zu) failed\n", file, line, size);
        exit(EXIT_FAILURE);
    }
    return ptr;
}


void xfree_debug(void* ptr, const char* file, int line) {
    if (!ptr) {
        fprintf(stderr, "[%s:%d] Warning: attempt to free NULL pointer\n", file, line);
        return;
    }
    free(ptr);
}