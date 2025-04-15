#include "complex.h"
#include <iostream>

int main(){
    Complex c1;
    Complex c2 = 3.0;
    Complex c3(3.0, 4.0);
    Complex c4 = c3; // Complex c4(c3);

    c1 = c3;         // 컴파일러에서 c1.operator=(c3) or operator=(c1, c3)형태로 바꿔서 호출함
    // c1 = c2 = c3;    // daisy-chain. c2 = c3의 결과값은 c2임 결과값이 없는 것이 아님 //더하기 빼기 연습으로 가림

    if(c1 == c3){    // 컴파일러에서 operator==(c1, c3) or c1.operator==(c3)형태로 바꿔서 호출함
        std::cout << "c1 and c3 are equal" << std::endl;
    }else{
        std::cout << "c1 and c3 are noet equal" << std::endl;
    }

    c4 = c2 + c3; //더하기 연산 만들어 보자 c2.operator+(c3) or operator+(c2, c3);
    c3 = c1 - c2;

    //std::cout << c1;        //(3.0, 4.0)   std::cout.operator<<(c1) : 불가능 ,  operator<<(std::cout, c1) : 가능 의 형태로 만들어주면 작동할거임
    // cout은 ostream의 타입이다. 라이브러리에 멤버함수를 추가하거나 전역함수 형태로 연산자 중복을 해줘야하는제 전자는 누가하냐. 전역함수 형태로 연산자 중복이나 해라
    std::cout << c1 << std::endl;
    std::cout << c2 << std::endl;
    std::cout << c3 << std::endl;
    std::cout << c4 << std::endl;

    
    return 0;
}