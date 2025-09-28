#include "list.h"

int main() {
    Node* head = createList();

    for (int i = 1; i <= 5; i++) {
        insertNode(&head, i);
    }

    printList(head); // 输出: 5 -> 4 -> 3 -> 2 -> 1 -> NULL

    freeList(head);
    return 0;
}
