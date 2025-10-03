#ifndef DATASRUCT_SYACK
#define DATASRUCT_SYACK

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


typedef struct stack {
    int* data;
    int* mindata;
    int top;
    int mintop;
} stack;

stack* initStack();

void freeStack(stack* st);

int getStackMinVal(stack* st);

bool isStackEmpty(stack* st);

void pushStack(stack* st, int val);

int topStack(stack* st);

int popStack(stack* st);
#endif