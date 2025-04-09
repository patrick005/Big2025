#include "list.h"
#include <stdio.h>

int main() {
    List list1, list2, list3, list4, list5;

    // 리스트 1 생성 및 초기화: [4, ]
    initList(&list1);
    insertFirstNode(&list1, 4);
    printList(&list1);
    cleanupList(&list1);

    // 리스트 2 생성 및 초기화: [3, 4, ]
    initList(&list2);
    insertFirstNode(&list2, 4);
    insertFirstNode(&list2, 3);
    printList(&list2);
    cleanupList(&list2);

    // 리스트 3 생성 및 초기화: [1, 3, 4, ]
    initList(&list3);
    insertFirstNode(&list3, 4);
    insertFirstNode(&list3, 3);
    insertFirstNode(&list3, 1);
    printList(&list3);
    cleanupList(&list3);

    // 리스트 4 생성 및 초기화: [1, 2, 3, 4, ]
    initList(&list4);
    insertFirstNode(&list4, 4);
    insertFirstNode(&list4, 3);
    insertFirstNode(&list4, 2);
    insertFirstNode(&list4, 1);
    printList(&list4);
    cleanupList(&list4);

    // 리스트 5 생성 및 초기화: [1, 2, 4, ]
    initList(&list5);
    insertFirstNode(&list5, 4);
    insertFirstNode(&list5, 2);
    insertFirstNode(&list5, 1);
    printList(&list5);
    cleanupList(&list5);

    return 0;
}