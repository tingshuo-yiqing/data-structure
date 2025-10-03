#include "stack.h"

int main() {
    stack* st = initStack();

    printf("%d\n", isStackEmpty(st));

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        int val;
        scanf("%d", &val);
        pushStack(st, val);
    }

    printf("%d\n", isStackEmpty(st));

    while (!isStackEmpty(st)) {
        printf("此时栈顶为%d 栈中最小值为%d\n", topStack(st), getStackMinVal(st));
        popStack(st);
    }

    freeStack(st);
    return 0;
}