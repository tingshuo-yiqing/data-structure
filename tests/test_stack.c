#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "stack.h"


int main() {
    stack* st = initStack(10000);

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

    puts("====后缀求值====");
    printf("%d\n%d\n%d\n", evalRPN(test1, len1), evalRPN(test2, len2), evalRPN(test3, len3));

    char test4[] = "2 1 + 3 *";  // 9
    char test5[] = "4 13 5 / +"; // 6
    char test6[] = "10 6 9 3 + -11 * / * 17 + 5 +";  // 22

    puts("====后缀转中缀====");
    char* test7 = postfixToInfix(test4);
    char* test8 = postfixToInfix(test5);
    char* test9 = postfixToInfix(test6);    
    printf("%s\n%s\n%s\n", test7, test8, test9);
    
    puts("====中缀转后缀====");
    char* test10 = infixToPostfix(test7);
    printf("%s\n", test10);
    char* test11 = infixToPostfix(test8);
    printf("%s\n", test11);
    char* test12 = infixToPostfix(test9);
    printf("%s\n", test12);

    puts("====中缀求值====");
    printf("%d\n", evalInfix(test7));
    printf("%d\n", evalInfix(test8));
    printf("%d\n", evalInfix(test9));

    freeStack(st);
    return 0;
}
