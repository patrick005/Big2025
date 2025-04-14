#include "complex.h"


Complex::Complex(double re, double im){
    this->re = re;
    this->im = im;
}
Complex::Complex(double re){ // double im로 못 만드는 이유: 이미 타입과 개수가 같은 re로 만들었기에 추가 생성 불가
    this->re = re;
    this->im = 0.0;
}
Complex::Complex(){
    this->re = 0.0;
    this->im = 0.0;
}

Complex::~Complex(){

}

double Complex::real(){

    return this->re;
}
double Complex::imag(){

    return this->im;
}

void Complex::real(double re){
    this->re = re;
}
void Complex::imag(double im){
    this->im = im;
}