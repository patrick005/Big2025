#include <cstring>  // C 스타일 문자열 함수를 위한 헤더
#include <string>   // C++ 문자열 클래스 (std::string)를 사용하기 위한 헤더
#include <iostream> // C++ 표준 입출력 스트림을 위한 헤더 (std::cout 사용)

int main(){
    // C 언어에서는 문자열을 char형 배열로 다루었지만,
    // C++에서는 더 편리하고 안전한 std::string 타입을 제공합니다.
    std::string s1;
    std::string s2 = "hello, ";

    // C 언어에서 문자열 복사는 strcpy() 함수를 사용했지만,
    // C++에서는 단순한 대입 연산자(=)를 사용하여 std::string 객체를 복사할 수 있습니다.
    s1 = s2; // s2의 내용을 s1에 복사합니다. 이제 s1도 "hello, "를 가집니다.
    
    // C 언어에서 문자열 결합은 strcat() 함수를 사용했지만,
    // C++에서는 더 직관적인 더하기 연산자(+)를 사용하여 std::string 객체를 결합할 수 있습니다.
    s1 = s1 + "world"; // s1의 내용("hello, ")에 "world" 문자열을 결합하여
                       // s1은 이제 "hello, world"를 가집니다.

    // C 언어에서 표준 출력은 printf() 함수를 사용했지만,
    // C++에서는 std::cout 객체와 << 연산자를 사용하여 다양한 타입을 출력할 수 있습니다.
    std::cout << s1 << std::endl;

    // C 언어에서 문자열의 길이를 얻기 위해 strlen() 함수를 사용했지만,
    // C++의 std::string 객체는 size() 또는 length() 멤버 함수를 제공하여
    // 문자열의 길이를 더 쉽게 얻을 수 있습니다.
    std::cout << s1.size() << std::endl;

    return 0;
}
