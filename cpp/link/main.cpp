#include "list.h"
// #include <stdio.h>
#include <cstdio>

int main() {
    List list1;
    // initList();
        
    list1.insertFirstNode(4);
    list1.printList();
    list1.insertFirstNode(3);
    list1.printList();
    list1.insertFirstNode(1);
    list1.printList();
    list1.insertNode(1, 2);
    list1.printList();
    
    list1.deleteNode(3);
    list1.printList();
    
    // list1.cleanupList();  
    // list1.~List();  

    return 0;
}