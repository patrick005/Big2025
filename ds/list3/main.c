#include "list.h"
#include <stdio.h>

void printInt(const void *pData){
    int i = *(int *)pData;
    printf("%d", i);
}
void printDouble(const void *pData){
    double d = *(double *)pData;
    printf("%f", d);
}

int main(void) {
    List list, list2;
    initList(&list, sizeof(int));
    initList(&list2, sizeof(double));
    
    int i;
    i = 4; insertFirstNode(&list, &i);
    i = 3; insertFirstNode(&list, &i);
    i = 1; insertFirstNode(&list, &i);
    int j = 1;
    i = 2; insertNode(&list, &j, &i);
    i = 3; deletNode(&list, &i);
    printList(&list, printInt);

    double d;
    d = 4.4; insertFirstNode(&list2, &d);
    d = 3.3; insertFirstNode(&list2, &d);
    d = 1.1; insertFirstNode(&list2, &d);
    double f = 1.1;
    d = 2.2; insertNode(&list2, &f, &d);
    d = 3.3; deletNode(&list2, &d);
    printList(&list2, printDouble);

    cleanupList(&list);
    cleanupList(&list2);

    return 0;
}
