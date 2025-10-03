#include "list.h"

int main() {

    Node* head1 = NULL;

    int a[] = {120, 34, 45, 64, 74};

    head1 = arrayToList(a, 5);
    
    printList(head1);
    return 0;
}
