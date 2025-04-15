//main.cpp
#include <iostream>
#include "empty.h"

int main(){
    Empty e1;               //생성자
    // empty.h에서 Empty(){} 주석 처리되었지만, 컴파일러가 자동으로 기본 생성자를 제공

    Empty e2 = e1;          //복사 생성자
    // empty.h에서 Empty(const Empty& rhs){} 주석 처리되었지만, 컴파일러가 자동으로 복사 생성자를 제공하며, 멤버별 복사를 수행

    e1 = e2;                //치환 연산자
    // empty.h에서 Empty& operator=(const Empty& rhs){} 주석 처리되었지만, 컴파일러가 자동으로 복사 대입 연산자를 제공하며, 멤버별 복사가 수행

    Empty *p1 = &e1;        //e1.operator() &연산도 제공
    // empty.h에서 Empty* operator&(){} 주석 처리되었지만, 주소 연산자는 모든 객체에 대해 컴파일러가 기본적으로 제공

    const Empty e3;
    const Empty *p2 = &e3;  //const 붙은 상수객체를 통해 호출
    // empty.h에서 const Empty* operator&() const{} 주석 처리되었지만, 상수 객체에 대한 주소 연산자 또한 컴파일러가 기본적으로 제공

    return 0;
}