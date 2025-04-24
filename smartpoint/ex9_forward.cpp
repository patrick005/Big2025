//ex9_forward.cpp
#include <iostream>
#include <utility>
using namespace std;

void process(string &&s){ //&&는 memory foward로 인한 메모리 이동을 받겠다는 기호이다 
    cout << "Rvalue:  참조 : " << s << endl;
}

void wrapper(string &&s){
    process(forward<string>(s));
}

int main(){
    wrapper(string("hello, world!!"));

    return 0;
}

/*
sting&&의 정의를 살펴보면 noexcept가 달려있다 이는
except상황이 많이 발생하는데 throw catch로 예외상황을 처리를 하는데, noexcept 키워드는 예외상황이 발생하더라도
다 실행하고 예외처리를 해라라는 키워드이다.

리터럴 상수는 Rvalue에 속함
int a = 3; -> Rvalue
3 = 3; -> error 
Rvalue의 상태를 wrapper에서 받게 되면 Lvalue로 변환이 됨
함수를 넘기면 복사라 생각을 하지만 move를 시키면 복사가 아닌 이동이며 메모리 복사가 안 일어난다.

*/