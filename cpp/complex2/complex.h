#ifndef COMPLEX_H
#define COMPLEX_H


class Complex{
public:
    Complex();                  //default constructor 기본입력이 없는 애들을 기본생성자/기저생성자 라고 부름
    Complex(double re);         // convert. constructor 변환 생성자
    Complex(double re, double im);
    ~Complex();

    double real();
    double imag();

    void real(double re);
    void imag(double im);


private:
    double re;
    double im;
};

#endif 
