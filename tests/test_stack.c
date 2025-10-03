#include "stack.h"


int main() {
    stack* st = initStack();

    printf("%d\n", isStackEmpty(st));
    return 0;
}