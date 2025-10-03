#include "stack.h"

#define CAPACITY 1001

stack* initStack() {
    stack* ret = (stack*)malloc(sizeof(stack));
    //! 直接赋值给结构体成员
    ret->data = (int*)malloc(sizeof(int) * CAPACITY);    
    ret->mindata = (int*)malloc(sizeof(int) * CAPACITY);    
    ret->top = -1;
    ret->mintop = -1;
    return ret;
}


void freeStack(stack* st) {
    if (st) {
        free(st->data);
        free(st->mindata);
        free(st);
    }
}


bool isStackEmpty(stack* st) {
    return st->top == -1;
}


int getStackMinVal(stack* st) {
    return st->mindata[st->mintop];
}


void pushStack(stack* st, int val) {
    st->data[++(st->top)] = val;
    if (isStackEmpty(st) || val <= st->mindata[st->mintop]) {
        st->mindata[++(st->mintop)] = val;
    } else {
        //! 拆开来写更清晰
        st->mintop++;
        st->mindata[st->mintop] = st->mindata[st->mintop - 1];
    }
}


int topStack(stack* st) {
    return st->data[st->top];
}

int popStack(stack* st) {
    return st->data[--(st->top)];
}
