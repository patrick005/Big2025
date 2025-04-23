//ex5_memoryLeak.cpp
// 메모리 리킹 문제편
// 메모리 리킹 해결편은 ex6_weakedPtr.cpp
#include <memory>
#include <iostream>
using namespace std;

class B;

class A{
public:
    shared_ptr<B> b_ptr;
    ~A(){cout << "A 소멸"<< endl;} // -> 만들어도 무시됨...
};
class B{
    public:
        shared_ptr<A> a_ptr;
        ~B(){cout << "B 소멸"<< endl;}
};

int main(){
    auto a = make_shared<A>();
    auto b = make_shared<B>();//여기까진 문제가 없음

    //이순간 순환 참조 발생
    a->b_ptr = b;
    b->a_ptr = a;

    return 0;
}


/*
순환참조 문제편

빌드에서는 아무 문제도 없다고 넘김
실행 시에 A 객체와 B 객체가 서로를 shared_ptr로 참조하여 참조 카운트가 0이 되지 않음

순환 참조가 발생하면 shared_ptr의 참조 카운트가 0이 되지 않아 객체가 소멸되지 않는 것이 문제의 핵심
반복적으로 이 프로그램을 실행시 (일정량)*n의 메모리를 사용하지 못함으로 메모리리킹이라고 함

+ 소멸자 추가해도 소멸자가 안돌고 있는 상황

*/