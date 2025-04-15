#ifndef COMPLEX_H
#define COMPLEX_H


class Complex{
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



};

#endif 
