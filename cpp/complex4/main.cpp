#include <iostream>
#include "complex.h"

int main()
{
    Complex c1;
    Complex c2 = 3.0;
    Complex c3(3.0, 4.0);
    Complex c4 = c3;        // 복사생성자를 만들어주지 않았지만 정상 동작 - 컴파일러가 각각의 멤버들을 치환하는 복사 생성자를 만들어줌

    c1 = c3;                // 치환연산 에러없이 실행되는 것 확인 - 컴파일러가 각각의 멤버들을 치환하고 자기자신을 리턴하는 치환 연산자 만들어줌

    c1 == c3;               // 이건 동작하지 않아서 생성자 만들어줌
    c1 != c3;               // 이 식의 결과 값은 true, false 되면서 끝남

    c1 = c2 + c3;
    c1 = c2 - c3;
    c1 += c2 += c3;               // 이 식의 결과 값은 c1
    
    ++c1;
    c1++;

    std::cout << "c1 : " << c1 << std::endl;
    std::cout << "c2 : " << c2 << std::endl;
    std::cout << "c3 : " << c3 << std::endl;
    std::cout << "c4 : " << c4 << std::endl;

    const Complex c5(3.0, 5.0);
    // c5.real(4.0);
    std::cout << "c5 : " << c5.real() << ", " << c5.imag() << "i)" << std::endl;

    return 0;
}