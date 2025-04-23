//ex4_shared_ptr.cpp
#include <memory>
#include <iostream>
using namespace std;

int main(){
    auto a = make_shared<int>(100); 
    auto b = a; // 포인터에 대한 참조가 생김
    auto c = a;


    cout << "a use_cout: " << a.use_count() << endl;
    cout << "b use_cout: " << b.use_count() << endl;

    return 0;
}


/*
출력은 둘다 3임
3명이 서로 공유중이라 묶인 거임

*/