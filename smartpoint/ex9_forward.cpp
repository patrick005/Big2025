//ex9_forward.cpp
#include <iostream>
#include <utility>
#include <string>
#include <stdexcept> // noexcept 관련 

using namespace std;

void process(string &&s){ //&&는 memory foward로 인한 메모리 이동을 받겠다는 기호이다 // Rvalue 참조 받음 (이동 가능)
    cout << "Rvalue:  참조 : " << s << endl;
}

void wrapper(string &&s){// Rvalue 참조 받음
    process(forward<string>(s));// 완벽 전달: 원래 속성 유지하여 process 호출
}

int main(){
    wrapper(string("hello, world!!"));// 임시 객체 (Rvalue) 전달

    return 0;
}

/*
sting&&의 정의를 살펴보면 noexcept가 달려있다 이는
except상황이 많이 발생하는데 throw catch로 예외상황을 처리를 하는데, noexcept 키워드는 함수가 예외를 던지지 않음을 명시하는 키워드


리터럴 상수는 Rvalue에 속함
int a = 3; -> Rvalue
3 = 3; -> error 
Rvalue의 상태를 wrapper에서 받게 되면 Lvalue로 변환이 됨
함수를 넘기면 복사라 생각을 하지만 move를 시키면 복사가 아닌 이동이며 메모리 복사가 안 일어난다.

*** 제미니 정리 ***
string&&: Rvalue 참조 타입. noexcept는 함수 속성 (예외 미발생 명시).
Rvalue (임시 객체)는 대입 연산자 왼쪽에 올 수 없음.
함수 내 rvalue 참조 매개변수는 lvalue로 취급.
forward<T>(arg): arg의 원래 값 속성 (lvalue/rvalue) 유지하며 전달 (완벽 전달).
move: 객체를 rvalue 참조로 캐스팅하여 이동 연산 활성화.
*/