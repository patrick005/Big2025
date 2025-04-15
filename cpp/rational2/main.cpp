#include "rational.h"
#include <iostream>


int main(){
    Rational r1(3, 4);  //3/4
    Rational r2(3);     //3/1
    Rational r3(6, 9);        //0/1 ==>비교분석을 위해 (0,0)에서 (6,8)로 변경, (6,9)로도 확인 환료

    // r3.SetNum(r1.getNum());
    // r3.SetDenom(r1.getDenom());

    // r3 = r1; 
    // 이 줄은 오버로드된 대입 연산자를 사용하여 r3을 r1의 복사본으로 만드는 방법.
    // 동등 비교 연산자를 테스트하기 위해 주석 처리.

    if(r1 == r3){// operator==(c1, c3) or c1.operator==(c3)
        std::cout << "r1 and r3 are equal" << std::endl;
    }else{
        std::cout << "r1 and r3 are noet equal" << std::endl;
    }

    std::cout << "r1 : " << r1.getNum() << "/" << r1.getDenom() << std::endl;
    std::cout << "r2 : " << r2.getNum() << "/" << r2.getDenom() << std::endl;
    std::cout << "r3 : " << r3.getNum() << "/" << r3.getDenom() << std::endl;
    // ~Rational();
    return 0;
}