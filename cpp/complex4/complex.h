#ifndef COMPLEX_H
#define COMPLEX_H
#include <iostream>

class Complex {
friend std::ostream& operator<<(std::ostream& out, const Complex& rhs);

private:
    double re_; // 변수 이름에 유일하게 쓸 수 있는 특수문자 (멤버변수라는 것을 강조하기위해 mRe, m_re 등으로 쓰기도함 - 가독성 향상)
    double im_;

public:
    Complex(double re = 0.0, double im = 0.0);  // Complex() { } - 디폴트 생성자 만들어지지 않음 , 디폴트 인자는 헤더파일에서 써야하고 뒤쪽부터 작성
    // Complex(const Complex& ) { } /* memberwise copy */
    // ~Complex() { }
    
    // Complex& operator=(const Complex& ) { /* memberwise copy */ return *this; }
    Complex& operator+=(const Complex& rhs);
    // +=, -=, *=, /=  ==> O 만들어 줘야함
    // %=, &=, |=, ^=  ==> X 만들어 주지 않아도 됨

    bool operator==(const Complex& rhs);
    bool operator!=(const Complex& rhs);
    // !=, >, <, >=, <= ==> O 만들어 줘야함

    const Complex operator+(const Complex& rhs); // 더하기 연산
    const Complex operator-(const Complex& rhs);
    // -, *, / ==> O 만들어 줘야함
    // % ==> X 만들어 주지 않아도 됨
    
    Complex& operator++();       // prefix (단항연산자라서 앞에 붙이는 경우와 뒤에 붙이는 경우 구별해줘야함. 이건 앞에 붙이는 경우)
    Complex operator++(int );   // postfix (뒤에 붙이는 경우)
    // ++, -- ==> X 만들어 주지 않아도 됨 정수형 변수에 대해서 증가연산, 감소연산 만드는거니까 어색하지만 연산자 중복 연습을 위해 만들어 주기로 함


    // &, |, ~, ^ ==> X 만들어 주지 않아도 됨

    // type casting ==> X 만들어 주지 않아도 됨

    // Complex *operator&() { return this; }
    // const Complex *operator&() const { return this; }
    double real();
    double imag();
    double real(double re);
    double imag(double im);

};
#endif
// 컴파일러가 자동으로 생성해주는 생성자 6가지 : 다 쓸 줄 알아야함
// 관례적으로 시스템 소프트웨어 함수는 _ 언더라인으로 시작하는 경우 있으나, 일반적인 어플리케이션에서는 잘 안씀