#include <stdio.h>
#include "memmgr.h"

int main(void) {
    printf("==== memmgr basic test ====\n");

    // 正常分配释放
    int *arr = XMALLOC(sizeof(int) * 5);
    if (!arr) {
        fprintf(stderr, "XMALLOC failed\n");
        return 1;
    }
    for (int i = 0; i < 5; i++) arr[i] = i;
    for (int i = 0; i < 5; i++) printf("%d ", arr[i]);
    printf("\n");
    XFREE(arr);  // 应打印释放日志

    // 释放 NULL
    int *p = NULL;
    XFREE(p);  // 应打印警告信息，不崩溃

    // 重复释放
    int *x = XMALLOC(sizeof(int) * 3);
    XFREE(x);
    XFREE(x);  // 再次释放，应打印 warning

    // 分配不同类型
    char *str = XMALLOC(sizeof(char) * 20);
    sprintf(str, "hello");
    printf("str = %s\n", str);
    XFREE(str);

    printf("==== test finished ====\n");
    return 0;
}
