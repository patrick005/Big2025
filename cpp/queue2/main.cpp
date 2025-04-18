#include "queue.h"
#include <iostream>

int main(){
    Queue q1(10);
    Queue q2;       //Queue q2(100); ->헤더에서 디폴트인자로 100줘서 성립됨
    //Queue q3 = q2; // 안쓸거같으니 생략 / 복사 생성자
    
    //q1 = q2;  //안쓸거같으니 생략 //치환연산자

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
