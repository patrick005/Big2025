#include "rational.h"
#include <cassert>
#include <numeric>  // 최대공약수(std::gcd) 사용

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
    // 원래 구현에 따라 void를 반환하지만, 메서드 체이닝을 허용하기 위해 객체 자신에 대한 참조(*this)를
    // 반환하는 것이 일반적인 관례입니다.
}

// 오버로드된 동등 비교 연산자
bool Rational::operator==(const Rational& other) const {
    Rational left = *this;  // 왼쪽 피연산자 Rational 객체의 복사본 생성
    Rational right = other; // 오른쪽 피연산자 Rational 객체의 복사본 생성
    left.normalize();       // 왼쪽 유리수 정규화
    right.normalize();      // 오른쪽 유리수 정규화

    // 정규화된 분자와 분모가 같은지 비교
    return left.num == right.num && left.denom == right.denom;

}

// 유리수를 정규화하는 함수
void Rational::normalize() {
    long long common_divisor = std::gcd(num, denom); // 최대공약수 계산
    num /= common_divisor;                           // 분자를 최대공약수로 나눔
    denom /= common_divisor;                         // 분모를 최대공약수로 나눔

    // 분모가 양수가 되도록 보장합니다. 음수이면 분자와 분모 모두 부호를 반전시킵니다.
    if (denom < 0) {
        num = -num;
        denom = -denom;
    }
}