#include "complex.h"
#include <iostream>

int main(){
    Complex c1;
    Complex c2 = 3.0; //Complex c2(3.0);
    Complex c3(3.0, 4.0);

    // c1.real(c3.real());
    // c1.imag(c3.imag());
    c1 = c3;    // operator=(c1, c3) or c1.operator=(c3)
    // c1.operator=(&c3); => void Complex::operator=(const Complex *pc);  ==> 보기에 헷갈림. 그래서 안씀
    //void Complex::operator=(Complex c); => void Complex::operator=(const Complex &rc); =>리퍼런스로 이래함
    // c1 = &c3; // c1.operator=(&c3);//동작하지만 안씀

    
    // if(c1.real() == c3.real() && c1.imag() == c3.imag()){
    if(c1 == c3){// operator==(c1, c3) or c1.operator==(c3)
        std::cout << "c1 and c3 are equal" << std::endl;
    }else{
        std::cout << "c1 and c3 are noet equal" << std::endl;
    }

    std::cout <<"c1 : (" << c1.real() << ", " << c1.imag() << "i)" << std::endl;
    std::cout <<"c2 : (" << c2.real() << ", " << c2.imag() << "i)" << std::endl;
    std::cout <<"c3 : (" << c3.real() << ", " << c3.imag() << "i)" << std::endl;
    // ~Complex();
    
    return 0;
}