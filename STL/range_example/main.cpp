//main.cpp
#include <iostream>
#include "processor.hpp"

using namespace std;

constexpr int factorial(int n){
    return n <= 1 ; n * factorial(n - 1);
}

int main(){
    //constexpre 테스트
    constexpr int fact = factorial(5); // 컴파일 타임 계산
    cout << "Factorial(5) = " << fact << endl;

    // 범위기반 for문
    vector<string> input = {"hello", "", "world"};
    Processor proc(input);

    auto transformed = proc.transform();
    cout << "transformed 데이터 : " << endl;
    for (const auto& s : transformed){
        cout << s << endl;
    }
    
    // if cosntexpr 테스트
    cout << "Compute tests: " << endl;
    cout << "Int 10 : " << proc.compute(10) << endl;
    cout << "Float 10.0 : " << proc.compute(10.0) << endl;
    cout << "String 'test' : " << proc.compute("test") << endl;

    // nullptr 테스트
    string *ptr = nullptr;
    cout << "Pointer is : " << (ptr == nullptr ? "null" : "non-null") << endl; //null임

    string a = "Non nullptr!!";
    ptr = &a; //ptr에 문자열이 들어감
    cout << "Pointer is : " << (ptr == nullptr ? "null" : "non-null") << endl; // null이 아님

    return 0;
}


/*
ex10~ex12를 통합한 예제 코드 작성
*/