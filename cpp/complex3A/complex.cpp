#include "complex.h"

std::ostream& operator<<(std::ostream& out, const Complex& rhs){ // 4. 멤버함수가 아닌 전역함수에서 private인 re, im에 접근하기에 에러뜸 -> 그래서 get함수를 만들어서 해결하던가 / cpp의 문법인 friend를 사용함
    out << "(" << rhs.re << ", " << rhs.im << "i)";

    return out; //3. 첫인자로 cout이 들어왔고 이를 출력하는 전역함수를 만들었음
}


Complex::Complex(double re, double im){
    this->re = re;
    this->im = im;
}

Complex::~Complex(){
}

Complex::Complex(const Complex& rhs){        //right hand side 피연산자가 오른쪽에 온다는 의미
    this->re = rhs.re;
    this->im = rhs.im;              //reference로 받고 일반변수처럼 사용
}

Complex& Complex::operator=(const Complex& rhs){ //타입은 &를 붙여서 레퍼런스로 넘어감
    this->re = rhs.re;
    this->im = rhs.im;

    return *this;
}
bool Complex::operator==(const Complex& rhs){
    // if((this->re = rhs.re )&& (this->im = rhs.im)){
    //     return true;
    // }else{
    //     return false;
    // }
    return (this->re == rhs.re && this->im == rhs.im);
}

const Complex Complex::operator+(const Complex& rhs){
    Complex result (this->re + rhs.re, this->im + rhs.im); //실수부, 허수부끼리 더한걸로 결과complex 구조체를 선언하고 그거 토해내면됨
    
    return result; //result는 지역 변수이기 때문에 레퍼런스로 반환이 안된다. 그래서 value값 자체를 반환해야한다
}
const Complex Complex::operator-(const Complex& rhs){
    Complex result (this->re - rhs.re, this->im - rhs.im);
    
    return result; 
}