#include "rational.h"
#include <cassert>

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