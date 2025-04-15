//string.h
#ifndef STRING_H
#define STRING_H
#include <iostream>

class String{
    // friend 선언을 통해 ostream& operator << 함수가 String 클래스의 private 멤버에 접근할 수 있도록 합니다.
    friend std::ostream& operator <<(std::ostream& out , const String& rhs);

private:
    char *str;
    int len;


public:
    String();                       //기본 생성자
    String(const char *s);          //char *를 인자로 받는 생성자
    String(const String& rhs);      //복사 생성자
    ~String();

    String& operator=(const String& rhs);       //대입 연산자 오버로딩

    bool operator==(const String& rhs);         //동등 비교 연산자 오버로딩

    const String operator+(const String& rhs);  //더하기 연산자 오버로딩

    const char *c_str();                        //내부 c 스타일 문자열 포인터 반환하는 const 매서드
    int size();


};

#endif