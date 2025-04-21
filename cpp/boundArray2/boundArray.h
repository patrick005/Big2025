#ifndef BOUNDARRAY_H
#define BOUNDARRAY_H

#include "safeArray.h"

template <typename T>
class BoundArray : public SafeArray<T>{
private:
    T low_;

public:

    explicit BoundArray(int size = Array<T>::size());    //-> 긴가민가함 오류확률높음
    // 하한(low)과 상한 직전 값(high)으로 초기화하는 생성자: 크기는 high - low
    BoundArray(T low, int upper);
    BoundArray(const BoundArray<T>& rhs);
    virtual ~BoundArray();
    
    BoundArray<T>& operator=(const BoundArray<T>& rhs);
    bool operator==(const BoundArray<T>& rhs)const;

    virtual T& operator[](int index);
    virtual const T& operator[](int index) const;

    int upper() const;
    int lower() const;

};
// boundArray.cpp
#include <cassert>

template <typename T>
BoundArray<T>::BoundArray(int size)
: SafeArray<T>(size)
{

}
template <typename T>
BoundArray<T>::BoundArray(T low, int upper)
: SafeArray<T>(upper - low), low_(low)
{
    assert(upper >= low);
    /* // 메인에 있는 숫자 자동 증감 할당을 하려면 이것 활성화
    for (int i = 0; i < this->SafeArray::size(); ++i) {
        this->SafeArray::operator[](i) = low_ + i;
    }
    */
}
template <typename T>
BoundArray<T>::BoundArray(const BoundArray<T>& rhs)
: SafeArray<T>((SafeArray<T>)rhs), low_(rhs.low_) //slicing하여 array관련 내용만 남게 타입캐스팅
{

}
template <typename T>
BoundArray<T>::~BoundArray(){

}

template <typename T>
BoundArray<T>& BoundArray<T>::operator=(const BoundArray<T>& rhs)
{
        if (this != &rhs){
        this->SafeArray<T>::operator=((SafeArray<T>)rhs);
        low_ = rhs.low_;
    }
    return *this;
}
template <typename T>
bool BoundArray<T>::operator==(const BoundArray<T>& rhs)const
{
    return (low_ == rhs.low_) && this->SafeArray<T>::operator==((SafeArray<T>)rhs);
}

template <typename T>
T& BoundArray<T>::operator[](int index) // 게이뭐람
{
    assert(index >= low_ && index < (low_ + this->Array<T>::size()));
    return this->SafeArray<T>::operator[](index - low_);
}
template <typename T>
const T& BoundArray<T>::operator[](int index) const
{
    assert(index >= low_ && index < (low_ + this->SafeArray<T>::size()));
    return this->SafeArray<T>::operator[](index - low_);
}

template <typename T>
int BoundArray<T>::upper() const{
    // 유효 인덱스 범위는 [low_, low_ + SafeArray::size()) 이므로 상한은 low_ + SafeArray::size()
    return low_ + this->Array<T>::size();
}

// lower() 함수 구현: 저장된 하한(low_) 반환 (const)
template <typename T>
int BoundArray<T>::lower() const{
    return low_;
}


#endif