//ex11_moveClass.cpp
#include <iostream>
#include <memory>
#include <string>
using namespace std;

class MyData{
private:
    string data_;

public:
    MyData(const string& d): data_(d){
        cout << "복사 생성자 호출" << endl;
    }
    MyData(const MyData& data) : data_("100"){
        
    }
    MyData(const string &&d) noexcept : data_(move(d)){
        cout << "이동 생성자 호출" << endl;
    }
    const string& get_data(){
        return data_;
    }
};

void useMyData(MyData &&data){
    cout << "복사 이동한 MyData" << endl;
    cout << data.get_data() << endl;
}

void referenceMyData(MyData & data){
    cout << "레퍼런스 data" << endl;
    cout << data.get_data() << endl;
}

int main(){
    string str = "hello";
    MyData d1(str);         // 복사생성자 호출
    MyData d2(move(str));   // 이동 생성자 호출
    // MyData d3(str);      -> 이동시켜서 str에 대한 복사가 안 됨(안 만들어짐) --> 이것의 테스트는 복사생성자 관련 부분 전부 주석 처리후 테스트하기
    // useMyData(d1);       -> 이동 생성자만 받을 수 있도록 함수를 설정했기에 못쓰는 표현 방법(실행 안 됨)
    useMyData(move(d2));    //복사 이동한 MyData, hello
    referenceMyData(d1);    // 레퍼런스 data, hello

    return 0;
}


/*
강사님 깃과 내용이 조금 다릅니다.
move를 한 것에 대해 이동과 복사를 시행했을 때 안되야 하지만 이를 구현해서 보여주려 했으나 실패하였고, 이에 대한 원인 설명을 못해주셨습니다.

이에 대해 개인적으로 조사한 내용입니다.

***제미니 답변 ***
이론적으로 "이동시켜서 str에 대한 복사가 안 됨(안 만들어짐)"이라고 생각하신 부분은 이동(move)의 의미를 조금 더 엄격하게 받아들이셨기 때문일 수 있습니다. 
move는 소유권 이전을 목표로 하지만, 실제로는 이동 생성자나 이동 대입 연산자가 어떻게 구현되었느냐에 따라 동작이 달라질 수 있습니다. 
특히 기본 타입이나 string과 같은 표준 라이브러리 타입의 경우, 이동 연산 후에도 원본 객체가 유효한 상태를 유지하는 경우가 많습니다 (하지만 그 값에 의존하는 것은 위험합니다).
결론적으로, MyData d3(str);가 되는 이유는 MyData 클래스가 const string& 타입의 lvalue 참조를 받는 복사 생성자를 제공하고, str은 lvalue이기 때문입니다. 
컴파일러는 lvalue를 const lvalue reference에 바인딩하여 복사 생성자를 호출하는 것이 합법적이라고 판단합니다.

***추가 질문***
원본 객체를 유지한다는건 흔적으로써 남기되, 메모리 공간에 여유가 없으면 다른 것을 할당 될 수 있기에 그것에 의존하는 것이 위험하다고 하는건가?

***추가 질문에 대한 제미니 답변***
정확히 이해하셨습니다! 
원본 객체를 move한 후에도 흔적처럼 남아있는 것은 맞습니다. 
대부분의 경우, 특히 string이나 표준 라이브러리 컨테이너의 이동 연산 후에도 원본 객체는 여전히 유효한 상태를 가집니다. 
즉, 소멸자가 호출되지 않았고, 기본적인 멤버 변수들은 여전히 존재합니다.
하지만 그 상태에 의존하는 것은 매우 위험합니다. 왜냐하면 move 연산의 핵심 의도는 자원의 효율적인 이전이기 때문입니다. 
이동 생성자나 이동 대입 연산자는 원본 객체의 자원을 대상 객체로 넘기고, 원본 객체를 유효하지만 "텅 빈" 상태로 만들 수 있습니다.
*/