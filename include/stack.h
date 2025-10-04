#ifndef DATASRUCT_SYACK
#define DATASRUCT_SYACK

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>

typedef int eletype;


typedef struct stack {
    eletype* data;
    eletype* mindata;
    int top;
    int mintop;
} stack;

stack* initStack();

void freeStack(stack* st);

int getStackSize(stack* st);

eletype getStackMinVal(stack* st);

bool isStackEmpty(stack* st);

void pushStack(stack* st, eletype val);

eletype topStack(stack* st);

eletype popStack(stack* st);

void clearStack(stack* st);

#endif