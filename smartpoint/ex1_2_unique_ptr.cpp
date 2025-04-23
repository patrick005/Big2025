//ex1_2_unique_ptr.cpp
#include <iostream>
#include <memory>
using namespace std;

class Myclass{
public:
    int test_a;
    Myclass(){
        cout << "Myclass 생성!!" << endl;
        test_a = 100;
    }
    ~Myclass() {cout << "Myclass 소멸!!" << endl;}
};


int main(){
    auto ptr = make_unique<Myclass>(); // heap에 만들어진 메모리
    // ptr->test_a = 100; --> 이걸 올린 버전
    // 에러상황에서도 동작을 함!!
    // 에러가 나면 할당된 부분은 반납을 해야하지만 이미 할당된걸 반납 안하는 경우가 있음
    // 이 부분에 있어서 스마트 메모리는 에러시 자동으로 힙영역의 메모리의 할당을 해제해주기 때문에 좋은것임
    cout << ptr->test_a << endl; 

    return 0;
}


/*
ex1_unique_ptr.cpp의 내용에 있던 주석을 제거하고 변경된 부분만 추가한 ver.2
*/