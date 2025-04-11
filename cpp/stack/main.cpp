//c의 전역함수를 cpp의 멤버함수로 변경하면서 구조체에 묶임
#include "stack.h"
// #include <stdio.h>
// #include <cstdio> // c가 아닌 cpp헤더
#include <iostream>

int main(){
    Stack s1(10), s2(100);  //생성자(객체가 생성될 때 자동적으로 호출되는 멤버함수)
    // initStack(&s1, 10);
    // initStack(&s2, 100);
    // s1.initStack(10);
    // s2.initStack(100);
    // s1.Stack(10);       //주석 처리를 해도 되는데 우린 사이즈를 받아야해서
    // s2.Stack(100);      //위에 Stack선언시에 사이즈 추가

    // push(&s1, 100);
    // push(&s1, 200);
    // push(&s1, 300);
    s1.push(100);
    s1.push(200);
    s1.push(300);

    // s1.tos = 0; //접근지정자 테스트용 코드

    // printf("s1 1st pop() : %d\n",pop(&s1));
    // printf("s1 2nd pop() : %d\n",pop(&s1));
    // printf("s1 3rd pop() : %d\n",pop(&s1));
    // printf("s1 1st pop() : %d\n", s1.pop());
    // printf("s1 2nd pop() : %d\n", s1.pop());
    // printf("s1 3rd pop() : %d\n", s1.pop());
    std::cout << "s1 1st pop() : " << s1.pop() << std::endl; //endl =\n
    std::cout << "s1 2nd pop() : " << s1.pop() << std::endl;
    std::cout << "s1 3rd pop() : " << s1.pop() << std::endl;
    
    // push(&s2, 900);
    // push(&s2, 800);
    // push(&s2, 700);
    s2.push(900);
    s2.push(800);
    s2.push(700);

    // printf("s2 1st pop() : %d\n",pop(&s2));
    // printf("s2 2nd pop() : %d\n",pop(&s2));
    // printf("s2 3rd pop() : %d\n",pop(&s2));
    // printf("s2 1st pop() : %d\n", s2.pop());
    // printf("s2 2nd pop() : %d\n", s2.pop());
    // printf("s2 3rd pop() : %d\n", s2.pop());
    std::cout << "s2 1st pop() : " << s2.pop() << std::endl;
    std::cout << "s2 2nd pop() : " << s2.pop() << std::endl;
    std::cout << "s2 3rd pop() : " << s2.pop() << std::endl;
    
    // cleanupStack(&s1);
    // cleanupStack(&s2);
    // s1.cleanupStack();
    // s2.cleanupStack();
    // s1.~Stack();  //안해도 컴파일러가해줌
    // s2.~Stack();
    return 0;  //소멸자(객체가 소멸될 때 자동적으로 호출되는 멤버함수)
}
//고정크기의 배열에서 가변크기의 배열(힙메모리)로 변경