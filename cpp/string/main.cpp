//main.cpp
#include <iostream>
#include "string.h"

int main()
{
    String s1 = "just the way you are"; // String s1("just the ...")
    String s2 = s1;                     // 복사 생성자
    String s3;                          // 디폴트 생성자

    // 대입 연산자를 사용하여 s1의 내용을 s3에 복사합니다.
    // String& operator=(const String& rhs)가 호출됩니다.
    s3 = s1;

    // bool operator==(const String& rhs)가 호출됩니다.
    if(s1 == s3){
        std::cout << "s1 and s3 are equal" << std::endl;
    }else{
        std::cout << "s1 and s3 are noet equal" << std::endl;
    }

    String s4 = " - bruno mars";

    // 더하기 연산자를 사용하여 s1과 s4를 결합한 새로운 String 객체를 생성하고
    // 그 결과를 s4에 대입합니다.
    // const String String::operator+(const String& rhs)와
    // String& String::operator=(const String& rhs)가 순서대로 호출됩니다.
    s4 = s1 + s4;

    std::cout << "s1: " << s1.c_str()<< ", " <<  s1.size() << std::endl;
    std::cout << "s2: " << s2 << ", " <<  s2.size() << std::endl;
    std::cout << "s3: " << s3 << ", " <<  s3.size() << std::endl;
    std::cout << "s4: " << s4 << ", " <<  s4.size() << std::endl;

    return 0;
}