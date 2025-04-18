#include "complex.h"

std::ostream& operator<<(std::ostream& out, const Complex& rhs)
{
    return out << "(" << rhs.re_ << ", " << rhs.im_ << "i)";
}

Complex::Complex(double re, double im)
{
    re_ = re;       // this->re_ = re;  /* this-> 는 생략가능한데, 멤버변수와 지역변수의 이름이 같을 때는 생략 불가 : 멤버변수가 지역변수로 덮어씌워진다. 지역변수가 지역변수로 치환되는 상황이 벌어짐 */
    im_ = im;       // this->im_ = im;
}

Complex& Complex::operator+=(const Complex& rhs)
{
    /*this->*/re_ += rhs.re_;
    /*this->*/im_ += rhs.im_;

    return *this;
}

bool Complex::operator==(const Complex& rhs)
{
    return this->re_ == rhs.re_ && this->im_ == rhs.im_;
}

bool Complex::operator!=(const Complex& rhs)
{
    // return !(re_ == rhs.re_ && this->im_ == rhs.im_); ==> 별로 안좋은가? 강사님이 이렇게 써도 된다고 하셨지만 지우심
    // return !(*this == rhs);
    return ! this->operator==(rhs); // 기존에 만들어져있는 멤버함수를 호출해서 사용하는 방법

    // return re_ != rhs.re_ || this->im_ != rhs.im_;
}

const Complex Complex::operator+(const Complex& rhs)
{
    Complex result(this->re_ + rhs.re_, this->im_ + rhs.im_);

    return result;
}

const Complex Complex::operator-(const Complex& rhs)
{
    Complex result(this->re_ - rhs.re_, this->im_ - rhs.im_);

    return result;
}

Complex& Complex::operator++()
{
    re_ += 1.0; // 복소수의 증가연산 이상한데, 일단 연습해야하니까 실수부에 더해줌

    return *this;
}

Complex Complex::operator++(int )
{
    Complex tmp = *this; // 자기 자신으로 임시 객체 만듦 변수가 하나 더 생성되면서 메모리 공간을 더 차지하게 되고 , 생성자와 소멸자 호출 -> 그만큼 오버헤드 , 지역변수에 대해서 레퍼런스 못넘김? 무슨말?
    re_ += 1.0;

    return tmp;
}

double Complex::real()
{
    return re_;
}

double Complex::imag()
{
    return im_;
}

void Complex::real(double re)
{
    re_ = re;
}

void Complex::imag(double im)
{
    im_ = im;
}
/*
the C programing language (일명 화이트북) 에서 증가연산자를 앞에 붙이던 관례때문에 앞에 붙이기도하고
C++ 에서는 내부적으로 이런 차이가 있다는걸 이해한다면 앞에 붙이게됨
하지만 C언어에서는 차이가 없는 것은 맞다.
*/ 

/*
Complex::~Complex() // 컴파일러가 만들어 주는 것 사용할 거라 안써줌 - 강사님은 명시적으로 쓰는거 선호 (사람마다 선호하는게 다름)
{

}
*/