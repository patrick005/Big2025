#ifndef RATIONAL_H
#define RATIONAL_H
#include <iostream>

class Rational {
friend std::ostream& operator<<(std::ostream& out, const Rational& rhs);

private:
    int num_; // numerator
    int den_; // denominator

    void reduce();  // helper func. tool func. ==> private 쪽에서 

public:
    Rational(int num = 0, int den = 1); // 생성자
    //Rational(const Ratioanl& ) { /* memberwise copy */}
    //~Rational() { }
    //Ratioanl& operator=(const Rational& ) { /* memberwise copy */ return *this; }

    bool operator ==(const Rational& rhs) const;
    bool operator !=(const Rational& rhs) const;

    const Rational operator+(const Rational& rhs) const;

    int num() const; 
    int den() const;

    void num(int num);
    void den(int den);

    // Getter
    int getNum() const;
    int getDen() const;

    // Setter
    void setNum(int num);
    void setDen(int den);

    // 사칙 연산자
    const Rational operator+(const Rational& rhs) const;
    const Rational operator-(const Rational& rhs) const;
    const Rational operator*(const Rational& rhs) const;
    const Rational operator/(const Rational& rhs) const;

    // 복합 대입 연산자
    Rational& operator+=(const Rational& rhs);
    Rational& operator-=(const Rational& rhs);

    // 비교 연산자
    bool operator==(const Rational& rhs) const;
    bool operator!=(const Rational& rhs) const;

    // 증가 연산자
    Rational& operator++();      // prefix
    Rational operator++(int);    // postfix
};

#endif