// boundArray.cpp
#include <cassert>
#include "boundArray.h"


BoundArray::BoundArray(int size)
: SafeArray(size), low_(0)
{
    for (int i = 0; i < this->SafeArray::size(); ++i) {
        this->SafeArray::operator[](i) = i; // SafeArray의 i번째 요소에 값 i 할당
    }
}
BoundArray::BoundArray(const int *pArr , int size)
: SafeArray(pArr, size), low_(0)
{

}
// 하한(low)과 상한 직전 값(high)으로 초기화하는 생성자 구현
BoundArray::BoundArray(int low, int high)
: SafeArray(high - low) // SafeArray 부분은 필요한 크기 (high - low)로 초기화
, low_(low)             // BoundArray의 하한은 low로 설정
{
    // 유효성 검사: high가 low보다 크거나 같아야 함
    assert(high >= low);
    /*
    for (int i = 0; i < this->SafeArray::size(); ++i) {
        this->SafeArray::operator[](i) = low_ + i;
    }
    */
}
BoundArray::BoundArray(const BoundArray& rhs)
: SafeArray((SafeArray)rhs), low_(rhs.low_)
{  
    //slicing하여 array관련 내용만 남게 타입캐스팅
}

BoundArray& BoundArray::operator=(const BoundArray& rhs)
{
        if (this != &rhs){
        this->SafeArray::operator=((SafeArray)rhs);
        // safearray 쪽에서 추가된게 있으면 여기에 추가
        this->low_ = rhs.low_;
    }
    return *this;
}
bool BoundArray::operator==(const BoundArray& rhs)const
{
    return (this->low_ == rhs.low_) && this->SafeArray::operator==((SafeArray)rhs);
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
