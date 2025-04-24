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
// 둘의 차이점: class의 public에 담으면 struct와 동일하게 사용
// c에서는 멤버함수를 넣을 수 없음
// c++에서는 class와 struct에 멤버함수를 넣을 수  있음
// c++에서의 차이: struct는 기본이 public(class private를 안쓴다면 struct로 써도 된다)

int main(){
    
    /* 
    스마트포인터 미사용 방법
    vector<Data> dataList;
    dataList.push_back(<Data>(1));
    dataList.push_back(<Data>(2));
    
    for(const auto& d : dataList){
        cout << d.value << endl;
        }
    */

    /*
    스마트 포인터 사용
    vector<shared_ptr<Data>> dataList;
    dataList.push_back(make_shared<Data>(1));
    dataList.push_back(make_shared<Data>(2));

    for(const auto& d : dataList){
        cout << d->value << endl;
}
*/

/* 
    스마트포인를 밖에 사용하는 방법 -> 안됨 */
    vector<shared_ptr<Data>> dataList;
    dataList.push_back(<Data>(1));
    dataList.push_back(<Data>(2));

    // shared_ptr<vector<Data>> dataList2;
    // dataList2->push_back(Data(10));
    // dataList2->push_back(Data(20));

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