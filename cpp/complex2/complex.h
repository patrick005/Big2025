#ifndef COMPLEX_H
#define COMPLEX_H


class Complex{
public:
    Complex();                  //default constructor 기본입력이 없는 애들을 기본생성자/기저생성자 라고 부름
    Complex(double re);         // convert. constructor 변환 생성자
    Complex(double re, double im);
    ~Complex();

    // void operator=(const Complex c);
    // void operator=(const Complex *pc);
    void operator=(const Complex& rc); //const = read only

    // int operator==(const Complex& rc); -> c type
    bool operator==(const Complex& re); // -> cpp type

    double real();
    double imag();

    void real(double re);
    void imag(double im);


private:
    double re;
    double im;
};

#endif 
