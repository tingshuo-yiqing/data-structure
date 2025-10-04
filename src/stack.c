#include "stack.h"

#define CAPACITY 1001

stack* initStack() {
    stack* ret = (stack*)malloc(sizeof(stack));
    //! 直接赋值给结构体成员
    ret->data = (eletype*)malloc(sizeof(eletype) * CAPACITY);    
    ret->mindata = (eletype*)malloc(sizeof(eletype) * CAPACITY);    
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


int getStackSize(stack* st) {
    return st->top + 1;
}


bool isStackEmpty(stack* st) {
    return st->top == -1;
}

eletype getStackMinVal(stack* st) {
    return st->mindata[st->mintop];
}


void pushStack(stack* st, eletype val) {
    st->data[++st->top] = val;
    if (st->mintop == -1 || val <= st->mindata[st->mintop]) {
        st->mindata[++st->mintop] = val;
    } else {
        //! 拆开来写更清晰
        st->mintop++;                       // 先自增
        st->mindata[st->mintop] = st->mindata[st->mintop - 1];  // 再赋值
    }
}


eletype topStack(stack* st) {
    return st->data[st->top];
}

eletype popStack(stack* st) {
    if (isStackEmpty(st)) return 0;
    // mindata也需要--
    st->mintop--;
    return st->data[st->top--];
}


void clearStack(stack* st) {
    // while (!isStackEmpty(st)) {
    //     popStack(st);
    // }
    // 因为没有释放内存所以直接把top和mintop置为-1即可
    st->top = -1;
    st->mintop = -1;
}