// #include <stdio.h>
#include "queue.h"
#include <iostream>

int main(){
    Queue q1(100), q2(10);
    // initQueue(&q1, 100);
    // initQueue(&q2, 10);

    // push(&q1, 100);
    // push(&q1, 200);
    // push(&q1, 300);
    q1.push(100);
    q1.push(200);
    q1.push(300);

    // printf("q1 1st pop() : %d\n", pop(&q1));
    // printf("q1 2nd pop() : %d\n", pop(&q1));
    // printf("q1 3rd pop() : %d\n", pop(&q1));
    std::cout << "q1 1st pop() : " << q1.pop() << std::endl;
    std::cout << "q1 2nd pop() : " << q1.pop() << std::endl;
    std::cout << "q1 3rd pop() : " << q1.pop() << std::endl;

    // push(&q2, 900);
    // push(&q2, 800);
    // push(&q2, 700);
    q2.push(900);
    q2.push(800);
    q2.push(700);

    // printf("q2 1st pop() : %d\n", pop(&q2));
    // printf("q2 2nd pop() : %d\n", pop(&q2));
    // printf("q2 3rd pop() : %d\n", pop(&q2));
    std::cout << "q2 1st pop() : " << q2.pop() << std::endl;
    std::cout << "q2 2nd pop() : " << q2.pop() << std::endl;
    std::cout << "q2 3rd pop() : " << q2.pop() << std::endl;

    // cleanupQueue(&q1);
    // cleanupQueue(&q2);
    // s1.~Queue();
    // s2.~Queue();
    return 0;
}
