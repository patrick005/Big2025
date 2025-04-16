#include <iostream>
#include "rational.h"

int main() 
{
    Rational r1;
    Rational r2 = 3;
    Rational r3(3, 4);
    Rational r4 = r3;
    Rational r5(9, 12);
    r1 = r2;

    r1 == r2;
    r1 != r2;

    r1 = r2 + r3;

    std::cout << "r1: " << r1 << std::endl;
    std::cout << "r2: " << r2 << std::endl;
    std::cout << "r3: " << r3 << std::endl;
    std::cout << "r4: " << r4 << std::endl;
    std::cout << "r5: " << r5 << std::endl;

    // std::cout << "r4: " << r4 << std::endl;

    // r1 += r2 += Rational(1, 2);
    // std::cout << "r1 after += : " << r1 << std::endl;

    // ++r1;
    // std::cout << "after ++r1: " << r1 << std::endl;

    // Rational r5 = r1++;
    // std::cout << "after r1++ (r1): " << r1 << std::endl;
    // std::cout << "after r1++ (r5): " << r5 << std::endl;

    // if (r1 != r2)
    //     std::cout << "r1 and r2 are not equal" << std::endl;

    return 0;
}