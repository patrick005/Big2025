#include <stdio.h>
#include "stack.h"

int main(void){
    push(100);
    push(200);
    push(300);

    int re = pop(); printf("1st pop() : %d\n", re);
    re = pop(); printf("2nd pop() : %d\n", re);
    re = pop(); printf("3rd pop() : %d\n", re);

    return 0;
}
// cc -c stack.c
// cc -c main.c
//cc -o testStack main.o stack.o

//gedit  main.c stack.h stack.c
