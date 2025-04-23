//ex6_weakedPtr.cpp
// 메모리 리킹 해결편
// 메모리 리킹 문제편은 ex5_memoryLeak.cpp

#include <memory>
#include <iostream>
using namespace std;

class B;

class A{
public:
    int a_var = 100;
    shared_ptr<B> b_ptr;
    ~A(){cout << "A 소멸"<< endl;} 
};
class B{
    public:
        int b_var = 200;
        weak_ptr<A> a_ptr;
        ~B(){cout << "B 소멸"<< endl;}
};

int main(){
    auto a = make_shared<A>();
    auto b = make_shared<B>();//여기까진 문제가 없음

    //이순간 순환 참조 발생
    a->b_ptr = b;
    b->a_ptr = a;

    // 해결편
    // cout << a->b_ptr->b_var << endl; // 이건 되는데
    // cout << b->a_ptr->a_var << endl; // 이건 안됨
    // b가 weak_ptr이라 접근을 막아둠 -> lock을 걸어버림

    cout << a->b_ptr->b_var << endl;
    cout << b->a_ptr.lock()->a_var << endl;
    // .lock()을 통해 이 라인에서만 쓰고 반납할게
    // 라고 허용 받아서 출력을 할 수 있게 함 

    return 0;
}


/*
순환참조 해결편
shared_ptr를 weak_ptr로 한군데라도 바꿔주면 해결

weak_ptr로 지정된 것에 대해서 lock()을 통해 해제를 하면 레퍼런스 카운트가 해당라인에선 증가하는 것을 볼 수 있음

*/