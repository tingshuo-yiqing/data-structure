#include "list.h"

int main() {
    Node* head = createList();

    insertNode(&head, 10);
    insertNode(&head, 20);
    insertNode(&head, 30);

    printList(head);  // 输出: 30 -> 20 -> 10 -> NULL

    freeList(head);
    return 0;
}
