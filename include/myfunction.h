#ifndef MY_FUNCTION
#define MY_FUNCTION

#ifdef __cplusplus
extern "C" {
#endif

#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>


#define MAX(a, b) ({       \
    __typeof__(a) _a = (a); \
    __typeof__(b) _b = (b); \
    _a > _b ? _a : _b;      \
})


#define MIN(a, b) ({       \
    __typeof__(a) _a = (a); \
    __typeof__(b) _b = (b); \
    _a < _b ? _a : _b;      \
})


#define ABS(x) ({ __typeof__(x) _x = (x); _x >= 0 ? _x : -_x; })


/*（支持任意类型） */
#define SWAP(a, b) do { \
    __typeof__(a) _tmp = (a); \
    (a) = (b); \
    (b) = _tmp; \
} while (0)


#define GCD(a, b) ({ \
    __typeof__(a) _a = (a) < 0 ? -(a) : (a); \
    __typeof__(b) _b = (b) < 0 ? -(b) : (b); \
    while (_b) { \
        __typeof__(_a) _t = _a % _b; \
        _a = _b; \
        _b = _t; \
    } \
    _a; \
})




#ifdef __cplusplus
}
#endif

#endif
