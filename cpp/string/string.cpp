//string.cpp
#include <cstring> // C 스타일 문자열 함수 (strcpy, strlen, strcmp, strcat)를 위한 헤더
#include "string.h"
#include <cassert>

// ostream 객체에 String 객체를 출력하기 위한 friend 전역 함수 오버로딩
std::ostream& operator<<(std::ostream& out , const String& rhs)
{
    // String 객체의 내부 C 스타일 문자열(str)을 ostream에 출력하고 ostream 객체를 반환.
    return out << rhs.str;
}

String::String()
{
    this->str = new char[1];
    this->str[0] = '\0';
    // 크기가 1인 char 배열을 동적으로 할당하고 첫 번째 문자를 널 종료 문자('\0')로 설정하여

    this->len = 0;
}

String::String(const char * s)
{
    // 입력된 C 스타일 문자열의 길이에 1을 더한 크기의 char 배열을 동적으로 할당.
    // 문자열만 카운트하기에 마지막 NULL을 위해 +1을 해줍니다
    this->str = new char[strlen(s) + 1];
    assert(this->str);
    strcpy(this->str , s);

    this->len = strlen(s);
}

// 복사 생성자: 다른 String 객체를 사용하여 현재 String 객체를 초기화.
String::String(const String& rhs)
{
    this->str = new char[rhs.len + 1];
    // 복사할 String 객체의 길이와 같은 크기의 char 배열을 동적으로 할당.

    assert(this->str);
    strcpy(this->str , rhs.str);

    this->len = rhs.len;
}

String::~String()
{
    delete [] this->str;
}

// 대입 연산자 오버로딩: 다른 String 객체의 내용을 현재 String 객체에 할당.
String& String::operator=(const String& rhs)
{
     // 현재 String 객체가 이미 가지고 있는 메모리를 해제.
     delete [] this->str;
     // 할당할 String 객체의 길이와 같은 크기의 새 메모리를 할당.
    this->str = new char[rhs.len];
    assert(this->str);
    strcpy(this->str, rhs.str);
    // 할당할 String 객체의 내용을 현재 객체의 메모리에 복사.

    this->len = rhs.len; // 현재 객체의 길이를 업데이트

    return *this;  // 자기 자신에 대한 참조를 반환하여 연쇄적인 대입을 지원
}

// 동등 비교 연산자 오버로딩: 두 String 객체의 내용이 같은지 비교.
bool String::operator==(const String& rhs)
{
    return strcmp(this->str , rhs.str) == 0;
}

// 더하기 연산자 오버로딩: 두 String 객체를 연결한 새로운 String 객체를 반환.
const String String::operator+(const String& rhs)
{   
    char buf[this->len + rhs.len + 1];
    // 현재 String 객체의 내용을 임시 버퍼에 복사.
    strcpy(buf, this->str);
    // rhs String 객체의 내용을 임시 버퍼의 현재 내용 뒤에 연결.
    strcat(buf, rhs.str);
    // 임시 버퍼의 내용으로 새로운 String 객체를 생성.
    String result(buf);

    return result;
}

// String 객체의 내부 C 스타일 문자열 포인터를 반환.
const char *String::c_str()
{
    return this->str;
}

int String::size()
{
    return this->len;
}
