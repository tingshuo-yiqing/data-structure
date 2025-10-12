#include "memmgr.h"

void* xmalloc_debug(size_t size, const char* file, int line) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "[%s:%d] malloc(%zu) failed\n", file, line, size);
        exit(EXIT_FAILURE);
    }
    // fprintf(stderr, "[%s:%d] Allocated %zu bytes at %p\n", file, line, size, ptr);
    return ptr;
}


void* xrealloc_debug(void* ptr, size_t size, const char* file, int line) {
    void* new_ptr = realloc(ptr, size);
    if (new_ptr == NULL) {
        fprintf(stderr, "[%s:%d] realloc(%p, %zu) failed\n", file, line, ptr, size);
        exit(EXIT_FAILURE);
    }
    // fprintf(stderr, "[%s:%d] Reallocated %zu bytes: %p -> %p\n", file, line, size, ptr, new_ptr);
    return new_ptr;
}


void xfree_debug(void* ptr, const char* file, int line) {
    if (!ptr) {
        fprintf(stderr, "[%s:%d] Warning: attempt to free NULL pointer\n", file, line);
        return;
    }
    // fprintf(stderr, "[%s:%d] Freed memory at %p\n", file, line, ptr);
    free(ptr);
}