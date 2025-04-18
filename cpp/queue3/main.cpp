// queue2와 달라진 것이 없음
#include "queue.h"
#include <iostream>

int main(){
    Queue q1(10);
    Queue q2;       

    q1.push(100);
    q1.push(200);
    q1.push(300);

    while (!q1.isEmpty()){
        std::cout << q1.pop() << std::endl;
    }

    std::cout << "q1 size: " << q1.size() << std::endl;
    std::cout << "q1 availability : " << q1.avab() << std::endl;

    return 0;
}
