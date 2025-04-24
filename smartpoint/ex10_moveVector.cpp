//ex10_moveVector.cpp

#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

int main(){
    vector<string> vec;
    constexpr int N = 100'000;

    // 실행시간이 걸리는 코드
    string str = "sample test";
    for (int i = 0; i < N; ++i){ 
        str += "sample test";
    }
    
    auto start = chrono::high_resolution_clock::now();
    // 복사: 새로운 string 객체 생성 및 내용 복사 (시간 오래 걸림)
    // vec.push_back(str);
    // 이동: string 객체의 내부 포인터만 복사 (시간 매우 짧음)
    vec.push_back(move(str));   // 두종류 비교를 위해 번갈아가며 주석걸기

    auto end = chrono::high_resolution_clock::now();
    cout << "이동시간: " << chrono::duration<double>(end - start).count() << "초" << endl;

    return 0;
}


/*
복사와 이동을 시켰을 때의 속도 비교를 위한 코드
- N번의 문자열 연결을 통해 큰 문자열 str 생성
- push_back 시 복사 vs 이동에 따른 시간 측정
- move(str)은 str의 소유권을 vec으로 이동시키므로 복사 비용이 발생하지 않음
*/