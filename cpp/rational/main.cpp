#include "rational.h"
#include <iostream>


int main(){
    Rational r1(3, 4);  //3/4
    Rational r2(3);     //3/1
    Rational r3;        //0/1

    r3.SetNum(r1.getNum());
    r3.SetDenom(r1.getDenom());

    std::cout << "r1 : " << r1.getNum() << "/" << r1.getDenom() << std::endl;
    std::cout << "r2 : " << r2.getNum() << "/" << r2.getDenom() << std::endl;
    std::cout << "r3 : " << r3.getNum() << "/" << r3.getDenom() << std::endl;
    // ~Rational();
    return 0;
}