#ifndef COMPLEX_H
#define COMPLEX_H


class Complex{
private:                 //implemetation
    double re;           //실수 real prt
    double im;           //허수 imaginary part

public: //interface
    Complex(double re, double im); //constructor
    Complex(double re);            //fuction overloading 함수 중복(인자의 타입, 인자의 개수가 달라야함)
    Complex();                     //이는 one-interface multi-method를 지원하기 때문임 
    // c++에서는 (함수의 이름, 인자의 타입, 인자의 개수, const의 유무)로 함수를 unique하게 구별함

    ~Complex();          //destructor

    
    // getset 함수
    double real();
    double imag();

    void real(double re);
    void imag(double im);
    

};

#endif 
