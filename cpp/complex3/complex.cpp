#include "complex.h"

Complex::Complex(double re, double im){
    this->re = re;
    this->im = im;
}

Complex::~Complex(){
}

Complex::Complex(const Complex& rhs){        //right hand side 피연산자가 오른쪽에 온다는 의미
    this->re = rhs.re;
    this->im = rhs.im;              //reference로 받고 일반변수처럼 사용
}

Complex& Complex::operator=(const Complex& rhs){ //타입은 &를 붙여서 레퍼런스로 넘어감
    this->re = rhs.re;
    this->im = rhs.im;

    return *this;
}
bool Complex::operator==(const Complex& rhs){
    // if((this->re = rhs.re )&& (this->im = rhs.im)){
    //     return true;
    // }else{
    //     return false;
    // }
    return (this->re == rhs.re && this->im == rhs.im);
}

