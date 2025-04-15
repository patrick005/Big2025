#ifndef RATIONAL_H
#define RATIONAL_H


class Rational{
private:                          //implemetation
    int num;                      //실수 real prt
    int denom;


public: //interface
    Rational(int num, int denom); //constructor
    Rational(int num);
    Rational();
    ~Rational();                  //destructor

    int getNum();
    int getDenom();
    
    void SetNum(int num);
    void SetDenom(int denom);
};

#endif 
