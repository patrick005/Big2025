// boundArray.cpp
#include <cassert>
#include "boundArray.h"


BoundArray::BoundArray(int size)
: SafeArray(size), low_(0)
{

}
BoundArray::BoundArray(int low, int upper)
: SafeArray(upper - low) // SafeArray 부분은 필요한 크기 (upper - low)로 초기화
, low_(low)             // BoundArray의 하한은 low로 설정
{
    assert(upper >= low);
    /* // 메인에 있는 숫자 자동 증감 할당을 하려면 이것 활성화
    for (int i = 0; i < this->SafeArray::size(); ++i) {
        this->SafeArray::operator[](i) = low_ + i;
    }
    */
}
BoundArray::BoundArray(const BoundArray& rhs)
: SafeArray((SafeArray)rhs), low_(rhs.low_) //slicing하여 array관련 내용만 남게 타입캐스팅
{

}
BoundArray::~BoundArray(){

}

BoundArray& BoundArray::operator=(const BoundArray& rhs)
{
        if (this != &rhs){
        this->SafeArray::operator=((SafeArray)rhs);
        low_ = rhs.low_;
    }
    return *this;
}
bool BoundArray::operator==(const BoundArray& rhs)const
{
    return (low_ == rhs.low_) && this->SafeArray::operator==((SafeArray)rhs);
}

int& BoundArray::operator[](int index)
{
    assert(index >= this->low_ && index < (this->low_ + this->SafeArray::size()));
    return this->SafeArray::operator[](index - this->low_);
}
const int& BoundArray::operator[](int index) const
{
    assert(index >= this->low_ && index < (this->low_ + this->SafeArray::size()));
    return this->SafeArray::operator[](index - this->low_);
}

int BoundArray::upper() const{
    // 유효 인덱스 범위는 [low_, low_ + SafeArray::size()) 이므로 상한은 low_ + SafeArray::size()
    return this->low_ + this->SafeArray::size();
}

// lower() 함수 구현: 저장된 하한(low_) 반환 (const)
int BoundArray::lower() const{
    return this->low_;
}
