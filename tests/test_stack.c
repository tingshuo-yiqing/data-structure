#include "stack.h"


int main() {
    stack* st = initStack();

    printf("%d", isStackEmpty(st));
    return 0;
}