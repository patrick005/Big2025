//ex13_array.cpp
#include <array>
#include <deque>
#include <iostream>
#include <list>
#include <set>
#include <unordered_map>
using namespace std;

int main()
{
    // array
    // 고정 크기 배열. STL 중 속도가 가장 빠르다. 그냥 배열 보다는 살짝 느림.
    array<int, 10> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (const auto &x : arr){
        cout << x << " ";
    }
    cout << endl;

    // deque -> 많은 메버 함수가 정의
    // 동적 크기, 양쪽 삽입/삭제 가능
    deque<int> dq = {1, 2, 3};
    dq.push_back(4);
    dq.push_front(0);
    dq.emplace_back(5);
    dq.emplace_front(-1);
    dq.insert(dq.begin() + 3, 2.5);

    for (const auto &v : dq){
        cout << v << " ";
    }
    cout << endl;

    dq.pop_back();
    dq.pop_front();

    for (const auto &v : dq){
        cout << v << " ";
    }
    cout << endl;

    // list 삽입 삭제 특화 -> linked list 형식임
    list<int> lst = {1, 2, 3};
    auto it = lst.begin();
    ++it;
    ++it;
    lst.insert(it, 3);
    for (const auto &v : lst){
        cout << v << " ";
    }
    cout << endl;

    // set -> 집합 // 중복이 없는 자료들, 자동 정렬
    set<int> s = {3, 1, 2, 2, 1};
    for (const auto &v : s){
        cout << v << " ";
    }
    cout << endl;
    cout << "s 집합의 크기는 " << s.size() << endl;

    //unorderd_map
    // 해쉬 테이블 기반의 자료 -> 아주아주 아주~ 빠른 접근
        // sha256..
    // 데이터가 굉장히 많을 때 100만개 이상.
    unordered_map<std::string, int> um = {{"apple", 100}, {"banana", 150}, {"mango", 200}};
    // 모든 것을 가지고 오려면 그냥 map 을 쓰세요.
    for (const auto &[key, val] : um)
    {
        cout << key << " : " << val << endl;
    }
    // 참조가 빠르다.
    cout << um["apple"] << endl;

    return 0;
}

/*
표준 라이브러리에 대해서 어떤 작동을 하는지 확인하는 코드를 작성함
*/