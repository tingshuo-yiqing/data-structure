#include "stack.h"
#include "memmgr.h"

#define CAPACITY 1001

stack* initStack() {
    stack* ret = XMALLOC(sizeof(stack));
    ret->data = XMALLOC(CAPACITY * sizeof(stack_eletype));
    ret->top = -1;
    ret->capacity = CAPACITY;
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
