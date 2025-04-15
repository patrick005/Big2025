#include "rational.h"
#include <cassert>
#include <numeric>

Rational::Rational(int num, int denom){
    assert(denom != 0);
    this->num = num;
    this->denom = denom;
}
Rational::Rational(int num){
    this->num = num;
    this->denom = 1;
}
Rational::Rational(){
    this->num = 0;
    this->denom = 1;
}
Rational::~Rational(){

}

int Rational::getNum(){
    return this->num;
}
int Rational::getDenom(){
    return this->denom;
}

void Rational::SetNum(int num){
    this->num = num;
}
void Rational::SetDenom(int denom){
    assert(denom != 0);
    this->denom = denom;
}

void Rational::operator=(const Rational& rr){
    this->num = rr.num;
    this->denom = rr.denom;
}

bool Rational::operator==(const Rational& other) const {
    Rational left = *this;
    Rational right = other;
    left.normalize();
    right.normalize();

    return left.num == right.num && left.denom == right.denom;

}

void Rational::normalize() {
    long long common_divisor = std::gcd(num, denom);
    num /= common_divisor;
    denom /= common_divisor;
    if (denom < 0) {
        num = -num;
        denom = -denom;
    }
}