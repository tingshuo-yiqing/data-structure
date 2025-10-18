#ifndef DATASTRUCT_STACK
#define DATASTRUCT_STACK

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

// #define stack_eletype Frame
#define stack_eletype char

// typedef struct {

// } Frame;


typedef struct stack {
    stack_eletype* data;
    int top;
    int capacity;
} stack;

/**
 * @brief Initialize a stack with default capacity
 * @return Pointer to the initialized stack
 */
stack* initStack(int capacity);

/**
 * @brief Free the stack and its data
 * @param st Stack to free
 */
void freeStack(stack* st);

/**
 * @brief Get the current size of the stack
 * @param st Stack to check
 * @return Size of the stack
 */
int getStackSize(stack* st);

/**
 * @brief Check if the stack is empty
 * @param st Stack to check
 * @return true if stack is empty, false otherwise
 */
bool isStackEmpty(stack* st);

/**
 * @brief Push a value onto the stack
 * @param st Stack to push to
 * @param val Value to push
 */
void pushStack(stack* st, stack_eletype val);

/**
 * @brief Get the top value of the stack without popping
 * @param st Stack to check
 * @return Top value of the stack
 */
stack_eletype topStack(stack* st);

/**
 * @brief Pop the top value from the stack
 * @param st Stack to pop from
 * @return Popped value from the stack
 */
stack_eletype popStack(stack* st);

/**
 * @brief Clear all elements from the stack
 * @param st Stack to clear
 */
void clearStack(stack* st);


int evalRPN(char** tokens, int tokenSize);

char* postfixToInfix(char* expr);

char* infixToPostfix(char* expr);

int evalInfix(char* expr);

#ifdef __cplusplus
}
#endif

#endif
