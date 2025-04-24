//ex7_vectorSmart.cpp
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class Data{
public:
    int value;
    Data(int v) : value(v) {}
};
// c에서의 struct
// c++ 에서의 class, struct
// 둘의 차이점: class의 기본 접근 지정자는 private, struct의 기본 접근 지정자는 public 입니다.
// class의 멤버를 public으로 선언하면 struct와 유사하게 외부에서 접근 가능합니다.
// c에서는 struct에 멤버 함수를 포함할 수 없습니다.
// c++에서는 class와 struct 모두에 멤버 함수를 포함할 수 있습니다.

int main(){
    
    /* 
    스마트포인터 미사용 방법: Data 객체를 직접 vector에 저장 (스택 메모리 사용)
    vector<Data> dataList;
    dataList.push_back(<Data>(1));
    dataList.push_back(<Data>(2));
    
    for(const auto& d : dataList){
        cout << d.value << endl;
        }
    */

    /*
    스마트 포인터 사용: Data 객체를 힙에 생성하고 shared_ptr로 관리
    vector<shared_ptr<Data>> dataList;
    dataList.push_back(make_shared<Data>(1));
    dataList.push_back(make_shared<Data>(2));

    for(const auto& d : dataList){
        cout << d->value << endl;
}
*/

/*
    스마트 포인터 적용 오류 예시: vector가 shared_ptr<Data>를 담도록 선언되었지만,
    Data 객체를 직접 push_back하려고 하면 타입 불일치로 인한 컴파일 에러가 발생합니다.
*/
   vector<shared_ptr<Data>> dataList;
   // dataList.push_back(Data(1)); // Error: shared_ptr<Data> 타입이 필요합니다.
   // dataList.push_back(Data(2)); // Error: shared_ptr<Data> 타입이 필요합니다.

/*
   shared_ptr로 vector 자체를 관리하는 것은 vector 내부 요소의 수명 관리와는 다른 문제입니다.
   아래 코드는 문법적으로 잘못되었습니다. shared_ptr은 포인터를 관리하며,
   vector의 멤버 함수를 간접적으로 호출하는 방식은 지원하지 않습니다.
*/
   // shared_ptr<vector<Data>> dataList2;
   // dataList2->push_back(Data(10)); // Error: shared_ptr<vector<Data>>는 push_back 멤버가 없습니다.
   // dataList2->push_back(Data(20)); // Error: shared_ptr<vector<Data>>는 push_back 멤버가 없습니다.

    for(const auto& d : dataList){
        cout << d.value << endl;
    }
    // for(const auto& d : dataList2){
    //     cout << d.value << endl;
    // }

    return 0;
}

/*
스마트 포인터를 미적용과 적용, 적용 방식에 대한 연습
*/