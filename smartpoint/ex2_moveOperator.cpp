//ex2_moveOperator.cpp
#include <iostream>
#include <memory>
using namespace std;



int main(){
    auto p1 = make_unique<int>(100); // 값이 100
    auto p2 = move(p1); // 이동
    // cout << "p1가 소유한 값: " << *p1 << endl; --> 세그먼트 오류 // 이동시켜서 없는거 출력하려니 에러 토함
    if (!p1){
        cout << "p1은 nullptr 입니다." << endl; 
    }
    cout << "p2가 소유한 값: " << *p2 << endl;
    
    return 0;
}