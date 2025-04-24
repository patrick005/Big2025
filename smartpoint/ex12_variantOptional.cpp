//ex12_variantOptional.cpp
#include <iostream>
#include <variant>
#include <string>
#include <optional>
#include <any>

using namespace std;

int main(){
    variant<int, string> data; // int or string type -> 공용체라고도 함 두 타입에 대해서 같은 메모리를 다룰때 variant를 사용함
    data = 42;
    cout << get<int>(data) << endl;
    data = string("hello");
    cout << get<string>(data) << endl;

    optional<int> maybeInt; // int일 수도 있고, 아닐 수도 있을 경우(데이터가 없을때 nullptr 이나 null값이 들어갈 수 있도록 조치하는 방법
    maybeInt = 10;
    if (maybeInt){
        cout << *maybeInt << endl;
    }
    
    any anything = 123;
    cout << any_cast<int>(anything) << endl;
    anything = string("hi");
    cout << any_cast<string>(anything) << endl;
    anything = 1.1 ;
    cout << any_cast<double>(anything) << endl;
    
    return 0;
}

/*
c17이후 도입된 타입 관련 템플릿임
variant는 데이터가 하나의 메모리에 저장될 때, 타입이 여러가지 일 경우
이것으로 된 자료에 대해 참조하여 부르는게 get<타입>(데이터) 이런방식임

optional은 지정 타입의 값이 있을 수도 있고, 없을 수도 있는 상황
내부적으로 포인터로 값이 들어가도록 오버로딩 되어 있으며 포인터에 값을 집어 넣음
따라서 포인터로 부름

any 넣을땐 어떤 타입이던 가능
뽑을땐 any_cast<변수 타입>(데이터)의 형식으로 뽑아야함
지금 void, auto, any에 대한 정의나 사용 방식을 설명해보고 제대로 이해하고 있는지 점검을 해보세요.

위 방식은 파이썬에서도 다룸
- 유연성을 다루기 때문임
- 파이썬 사용자에 의해서 17버전부터 유입된걸로 추정

*/