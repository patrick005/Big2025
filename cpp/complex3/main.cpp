#include "complex.h"
#include <iostream>

int main(){
    Complex c1;
    Complex c2 = 3.0;
    Complex c3(3.0, 4.0);
    Complex c4 = c3; // Complex c4(c3);

    c1 = c3;         // 컴파일러에서 c1.operator=(c3) or operator=(c1, c3)형태로 바꿔서 호출함
    c1 = c2 = c3;    // daisy-chain. c2 = c3의 결과값은 c2임 결과값이 없는 것이 아님

    if(c1 == c3){    // 컴파일러에서 operator==(c1, c3) or c1.operator==(c3)형태로 바꿔서 호출함
        std::cout << "c1 and c3 are equal" << std::endl;
    }else{
        std::cout << "c1 and c3 are noet equal" << std::endl;
    }

    
    return 0;
}