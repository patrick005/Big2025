#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
// class Complex;      //2. ostream 선언이 먼저나오니 미리 나온다고 언급 -> 6. friend로 위치가 변경되어 없어도 됨
// std::ostream& operator<<(std::ostream& out, const Complex& rhs); // 1. 전역함수 

class Complex{
    friend std::ostream& operator<<(std::ostream& out, const Complex& rhs); // 5. 전역함수를 friend로 한거지 멤버함수가 아님 / 위치때문에 헷갈리지 말기

private: // 멤버 변수를 Attribute(속성)이라고 함
    double re;
    double im;

public: // 멤버 함수를 method라고 함
    //one interface multi method
    Complex(double re = 0.0, double im = 0.0); //default argument
    Complex(const Complex& rhs);               //const = read only / copy constructor 복사인자는 const t타입의 인자가 된다
    ~Complex();

    Complex& operator=(const Complex& rhs);     //daisy-chain에 의해서 결국 출력값이 void가 아닌 출력 타입이 있긴함
    bool operator==(const Complex& rhs);

    //+,-,/,*
    const Complex operator+(const Complex& rhs); //더하기
    const Complex operator-(const Complex& rhs); //빼기

};

#endif 
