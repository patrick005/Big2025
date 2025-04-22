//ex12_constexprestion.cpp
#include <iostream>

using namespace std;

constexpr int square(int x){return x * x;}

template<typename T>
auto process(T value){
    if constexpr (is_integral_v<T>){
        return value + 1;
    }else{
        return value + 0.5;
    }
}

int main(){
    constexpr int result = square(5);
    cout << result << endl;
    cout << process(10)  << endl; // if실행
    cout << process(5.5) << endl; // else 실행
    return 0;
}


/*
constexpr은 컴파일 타임 상수를 정의하는 데 사용되며, #define과 같은 매크로 대신 타입 안전하고 스코프를 갖는 컴파일 타임 상수를 정의하는 데 유용합니다.
컴파일 타임 계산을 통해 복잡한 프로그램에서 런타임 오버헤드를 감소시키고 성능을 향상시키는 데 기여합니다.
C++11 이후로 도입되었으며, C++17에서 `if constexpr`과 같은 기능으로 더욱 확장되었습니다.

constexpr은 컴파일 타임에 값을 계산할 수 있는 상수를 정의하는 키워드
#define은 전처리 단계에서 텍스트를 단순하게 치환하는 역할을 합니다. 타입 검사를 거치지 않으며, 스코프 개념도 없습니다.
이로 인해 예기치 않은 부작용이나 오류가 발생할 수 있습니다

*/