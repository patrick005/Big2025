#include "list.h"
#include <stdio.h>

int main(void) {
    List list;
    initList(&list);
    
    insertFirstNode(&list, 4);
    printList(&list);
    insertFirstNode(&list, 3);
    printList(&list);
    insertFirstNode(&list, 1);
    printList(&list);

    insertNode(&list, 1, 2);
    printList(&list);
    
    deletNode(&list, 3);
    printList(&list);
        
    cleanupList(&list);    

    return 0;
}