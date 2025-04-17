//
#include "stack.h"
#include <iostream>

int main(){
    Stack s1(10);       // Stack s1 = 10; -> 불가능한 표현
    Stack s2;           // Stack s2(100);
    // Stack s3 = s2;  // 복사생성자 쓸일 없을거 같으니 패스
    
    s1.push(100);
    s1.push(200);
    s1.push(300);
    
    std::cout << "s1 capacity : " << s1.size() << std::endl;
    std::cout << "s1 availability : " << s1.avab() << std::endl; // 강사님은 remain으로함

    // s1 = s2;         // 대입연산 안쓸거같은디

    while (!s1.isEmpty()){ // 빌때까지 pop 반복
        std::cout << s1.pop() << std::endl;

    }
    

    // s1.~Stack();  //안해도 컴파일러가해줌
    // s2.~Stack();
    return 0;  //소멸자(객체가 소멸될 때 자동적으로 호출되는 멤버함수)
}


