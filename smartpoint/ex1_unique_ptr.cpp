//ex1_unique_ptr.cpp
#include <iostream>
#include <memory>
using namespace std;

class Myclass{
public:
    int test_a;
    
};


int main(){
    // unique_ptr<Myclass> ptr = make_unique<Myclass>();
    auto ptr = make_unique<Myclass>(); // 윗줄과 동일
    ptr->test_a = 100;
    cout << ptr->test_a << endl; //멤버연산자라 화살표를 사용해야함

    return 0;
}