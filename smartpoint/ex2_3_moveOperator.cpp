//ex2_2_moveOperator.cpp
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

    
void useUnique(unique_ptr<Myclass> ptr){
    cout << "함수 안에서 값 : " << ptr->test_a << endl;
}

int main(){
    auto p1 = make_unique<Myclass>(); // class의 test_a의 값의 권한을 가져옴
    auto p2 = move(p1); // 이동

    useUnique(move(p2)); // main함수에서 권한이 이 함수로 들어오는데 이거 출력 끝나고 할당값이 해제됨
    //그래서 밑에 nullptr이 뜸
    
    if (!p1){
        cout << "p1은 nullptr 입니다." << endl; 
    }else{
        cout << "p1가 소유한 값: " << p1->test_a << endl;
    }

    if (!p2){
        cout << "p2은 nullptr 입니다." << endl; 
    }else{
        cout << "p2가 소유한 값: " << p2->test_a << endl;
    }
    
    return 0;
}


/*
ex2_2_moveOperator.cpp의 내용에 있던 주석을 제거하고 변경된 부분만 추가한 ver.3
unique에서의 class를 가져와서 시도
*/