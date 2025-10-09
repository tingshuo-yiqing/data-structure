#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "stack.h"


int evalPostfix(char** token, int len) {
    stack* st = initStack();
    for (int i = 0; i < len; ++i) {
        char* ch = token[i];
        if (strcmp(ch, "+") == 0 || strcmp(ch, "-") == 0 || strcmp(ch, "*") == 0 || strcmp(ch, "/") == 0) {
            int b = popStack(st);
            int a = popStack(st);
            if (strcmp(ch, "+") == 0) {
                pushStack(st, a + b);
            }
            else if (strcmp(ch, "-") == 0) {
                pushStack(st, a - b);
            }
            else if (strcmp(ch, "*") == 0) {
                pushStack(st, a * b);
            }
            else if (strcmp(ch, "/") == 0) {
                pushStack(st, a / b);
            }
        } else {
            pushStack(st, atoi(ch));
        }
    }
    int ret = topStack(st);
    freeStack(st);
    return ret;
}


int main() {
    stack* st = initStack();

    //todo 基本栈操作测试 
    int nums[] = {12, 0, 1, -9, 7};

    for (size_t i = 0; i < sizeof(nums) / sizeof(int); ++i) {
        pushStack(st, nums[i]);
    }

    while (!isStackEmpty(st)) {
        printf("此时栈顶为%d 栈中元素个数为%d\n", topStack(st), getStackSize(st));
        popStack(st);
    }

    //todo 后缀表达式,可计算多位数
    char* test1[] = {"2","1","+","3","*"};  // 9
    int len1 = sizeof(test1) / sizeof(test1[0]);
    char* test2[] = {"4","13","5","/","+"}; // 6
    int len2 = sizeof(test2) / sizeof(test2[0]);
    char* test3[] = {"10","6","9","3","+","-11","*","/","*","17","+","5","+"}; // 22
    int len3 = sizeof(test3) / sizeof(test3[0]);

    printf("%d\n%d\n%d\n", evalPostfix(test1, len1), evalPostfix(test2, len2), evalPostfix(test3, len3));


    freeStack(st);
    return 0;
}