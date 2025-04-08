#include <stdio.h>
#include "queue.h"


int main(void){

    Queue q1, q2;
    initQueue(&q1);
    initQueue(&q2);


    push(&q1, 100);
    push(&q1, 200);
    push(&q1, 300);

    printf("q1 1st pop() : %d\n", pop(&q1));
    printf("q1 2nd pop() : %d\n", pop(&q1));
    printf("q1 3rd pop() : %d\n", pop(&q1));

    push(&q2, 100);
    push(&q2, 200);
    push(&q2, 300);
    
    printf("q2 1st pop() : %d\n", pop(&q2));
    printf("q2 2nd pop() : %d\n", pop(&q2));
    printf("q2 3rd pop() : %d\n", pop(&q2));

    return 0;
}
