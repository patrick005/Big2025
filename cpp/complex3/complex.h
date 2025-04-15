#ifndef COMPLEX_H
#define COMPLEX_H


class Complex{
private: // 멤버 변수를 Attribute(속성)이라고 함
    double re;
    double im;

public: // 멤버 함수를 method라고 함
    //one interface multi method
    Complex(double re = 0.0, double im = 0.0); //default argument
    Complex(const Complex& rhs);               //copy constructor 복사인자
    //const Complex&를 사용하는 이유는 원본 객체를 변경하지 않고 복사본을 만들기 위함
    ~Complex();

    Complex& operator=(const Complex& rhs);     //daisy-chain(a=b=c;)에 의해서 결국 출력값이 void가 아닌 출력 타입이 있긴함 
    // 확인 결과 Complex 참조 타입(객체 자신에 대한 참조를 반환하여 연속적인 대입을 지원)
    bool operator==(const Complex& rhs);



};

#endif 
