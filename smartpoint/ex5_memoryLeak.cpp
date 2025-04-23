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
실행시 메모리 리킹 시작임
실행도 잘 작동함 -> 메모리는 대략 16비트 정도 남아서 잡아먹고 있는 상황

+ 소멸자 추가해도 소멸자가 안돌고 있는 상황

*/