//ex6_iterator.cpp
// iterator는 배열의 요소를 가르키는 포인터이다/ C++에서는 포인터 쓰기가 애매해서 이걸쓰는데 그래서 중요함
#include <iostream>
#include <vector> //-->iterator정의 포함되어있음
using namespace std;

// class A : 
// public:
//     class B:

int main(){
    vector<int>::iterator it;
    vector<int> test_vector = {1, 2, 3, 4, 5, 6};

    for (it = test_vector.begin(); it != test_vector.end(); ++it){ // for 문 두번째
        cout << *it << endl;
    }

    cout << "----------1-----------" << endl;
    // iterator가 정의 되어있어야함 / 이 정의가 begin(), end()로 첫째와 마지막을 가리킬때만 for문을 사용할 수 있음
    // iterator의 역참조인 *it가 가능해야 한다.
    for (auto v : test_vector){ // 세번째 방식 모던 C++(복사해서 쓰기에 메모리 주소값이 변경됨)
        cout << v << endl;
    }
    cout << "----------2-----------" << endl;
    for (auto &v : test_vector){ // 컨테이너의 값을 변경
        cout << v << endl;
    }
    cout << "----------3-----------" << endl;
    for (const auto &v : test_vector){ // 메모리를 더 안 먹고(복사 안 하고) 값은 바꿈 -> 메모리 효율적으로 값 참고 할 때
        cout << v << endl;
    }


    return 0;
}