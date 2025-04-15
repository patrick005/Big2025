#include <iostream>
#include "empty.h"

int main(){
    Empty e1;               //생성자
    Empty e2 = e1;          //복사 생성자

    e1 = e2;                //치환 연산자

    Empty *p1 = &e1;        //e1.operator() &연산도 제공

    const Empty e3;
    const Empty *p2 = &e3;  //const 붙은 상수객체를 통해 호출

    return 0;
}