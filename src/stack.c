#define _POSIX_C_SOURCE 200809L   // 这会告诉 GCC：我要用 POSIX 标准中的扩展函数，比如 strdup()。
#include "stack.h"
#include "memmgr.h"
#include <string.h>
#include <ctype.h>


stack* initStack(int capacity) {
    stack* ret = XMALLOC(sizeof(stack));
    ret->data = XMALLOC(capacity * sizeof(stack_eletype));
    ret->top = -1;
    ret->capacity = capacity;
    return ret;
}


void freeStack(stack* st) {
    if (st) {
        XFREE(st->data);
        XFREE(st);
    }
}


int getStackSize(stack* st) {
    return st->top + 1;
}


bool isStackEmpty(stack* st) {
    return st->top == -1;
}


void pushStack(stack* st, stack_eletype val) {
    st->data[++st->top] = val;
}


stack_eletype topStack(stack* st) {
    return st->data[st->top];
}


stack_eletype popStack(stack* st) {
    if (isStackEmpty(st)) return 0;
    return st->data[st->top--];
}


void clearStack(stack* st) {
    st->top = -1;
}


/* 表达式问题 */

/* 逆波兰表达式求值 */

static int isSign(char *token) {
    return strcmp(token, "*") == 0 || strcmp(token, "-") == 0 ||
            strcmp(token, "/") == 0 || strcmp(token, "+") == 0; 
}

static int signCalc(char* token, int a, int b) {
    int ret;
    if (strcmp(token, "*") == 0) ret = a * b;
    else if (strcmp(token, "+") == 0) ret = a + b;
    else if (strcmp(token, "-") == 0) ret = b - a;
    else if (strcmp(token, "/") == 0) {
        if (b == 0) {
            fprintf(stderr, "Error: Division by zero!\n");
            exit(EXIT_FAILURE); // 或者返回一个特殊值
        }
        ret =  b / a;
    }
    return ret;
}

static int precedence(char* token) {
    if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0) return 1;
    if ( strcmp(token, "/") == 0 || strcmp(token, "*") == 0) return 2;
    return 0;
}


int evalRPN(char** tokens, int tokenSize) {
    int nums[100];
    int top = -1;

    for (int i = 0; i < tokenSize; ++i) {
        if (isSign(tokens[i])) {
            int a = nums[top--];
            int b = nums[top--];
            nums[++top] = signCalc(tokens[i], a, b);
        } else {
            nums[++top] = atoi(tokens[i]);
        }
    }
    return nums[0];
}

/* 后缀转中缀 */

char* postfixToInfix(char* expr) {
    char* data[100];
    int top = -1;
    
    char* token = strtok(expr, " ");
    while (token) {
        if (!isSign(token)) {
            data[++top] = strdup(token);
        } else {
            char* a = data[top--];
            char* b = data[top--];
            char buf[50001];
            snprintf(buf, sizeof(buf), "( %s %s %s )", b, token, a);
            data[++top] = strdup(buf);
        }
        token = strtok(NULL, " ");
    }
    return data[0];
}


/* 中缀求转后缀 */

char* infixToPostfix(char* expr) {
    char* data[100];
    int top = -1;
    // 初始化返回值
    static char ret[100];
    ret[0] = '\0';

    char* token = strtok(expr, " ");
    while (token) {
        if (strcmp(token, "(") == 0) {
            data[++top] = token;
        } 
        else if (strcmp(token, ")") == 0) {
            while (top >= 0 && strcmp(data[top], "(") != 0) {
                strcat(ret, data[top--]);  // 弹栈
                strcat(ret, " ");
            }
            top--;
        } 
        else if (isSign(token)) {  // 判断运算符
            while (top >= 0 && precedence(data[top]) >= precedence(token)) {
                strcat(ret, data[top--]);  // 弹栈
                strcat(ret, " "); 
            }
            data[++top] = token;
        } 
        else {  // 神域的是数字字符串
            strcat(ret, token);
            strcat(ret, " ");
        }
        token = strtok(NULL, " ");
    }

    while (top >= 0) {
        strcat(ret, data[top--]);
        strcat(ret, " "); 
    }
    // 去掉最后一个空格
    return ret;
}

/* 中缀求值 */

int evalInfix(char* expr) {
    int nums[100];
    char* ops[100];
    int topNums = -1;
    int topOps = -1;

    char* token = strtok(expr, " ");
    while (token) {
        if (strcmp(token, "(") == 0) {
            ops[++topOps] = token;
        } 
        else if (strcmp(token, ")") == 0) {
            while (topOps >= 0 && strcmp(ops[topOps], "(") != 0) {
                int a = nums[topNums--];
                int b = nums[topNums--];
                nums[++topNums] = signCalc(ops[topOps--], a, b);
            }
            topOps--;   // 去掉 （
        }
        else if (isSign(token)) {
            while (topOps >= 0 && precedence(ops[topOps]) >= precedence(token)) {
                int a = nums[topNums--];
                int b = nums[topNums--];
                nums[++topNums] = signCalc(ops[topOps--], a, b);
            }
            ops[++topOps] = token;
        } else {
            nums[++topNums] = atoi(token);
        }
        token = strtok(NULL, " ");
    }

    while (topOps >= 0) {
        int a = nums[topNums--];
        int b = nums[topNums--];
        nums[++topNums] = signCalc(ops[topOps--], a, b);
    }
    return nums[0];
}