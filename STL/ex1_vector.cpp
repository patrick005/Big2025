// ex1_vector.cpp
//배열이랑 같다 다른점은 스택이 아닌 힙(동적)으로 만들어진다
// 그래서 사이즈가 없어서 사이즈를 신경 안 쓰고 계속 넣을 수 있다

#include <iostream>
#include <vector>

using namespace std;

int main(){
    vector<int> v; //생성

    //추가
    v.push_back(1);
    v.push_back(12);
    v.push_back(123);
    v.push_back(1234);
    v.push_back(12345);
    v.push_back(123456);
    v.push_back(1234567);
    

    //삭제
    // vector<int>::iterator it;   //vector<int>::iterator라는 타입이 기니 auto로 대체하자 -> 뒤에 오는 타입에 대해 알아서 컴파일때 맞춰줌(런타임이 아님)
    // it = v.begin() + 2;
    auto it = v.begin() + 2;
    v.erase(it);    // 123 삭제

    v.at(0) = 2; // 원소에 접근해서 변경할 때

    // cout << "v의 1번째 원소는 : " << v[0] << endl;
    // cout << "v의 2번째 원소는 : " << v[1] << endl;
    // cout << "v의 3번째 원소는 : " << v[2] << endl;  // 두개만 넣고 이걸쓰면 rangeover가 뜬다 그러니 반복문을 써보자

    // for 문을 쓰는 첫 번째 방법
    for (int i = 0; i < v.size(); i++){
        cout << "v의 " << i+1 << " 번째 원소는 : " << v[i] << endl;
    }
    



    return 0;
}













