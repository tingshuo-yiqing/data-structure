#include "list.h"

int main() {

    Node* head1 = NULL;
    Node* head2 = NULL;

    int a[] = {120, 34, 45, 64, 74};

    head1 = arrayToList(a, 5);
    head2 = copyList(head1);
    
    printList(head1);
    printList(head2);
    return 0;
}
