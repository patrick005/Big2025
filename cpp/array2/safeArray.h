#ifndef SAFEARRAY_H
#define SAFEARRAY_H

#include "array.h"


template <typename T>
class SafeArray : public Array<T>{

private:

public:

    explicit SafeArray(int size = Array<T>::getDefaultArraySize());
    SafeArray(const T *pArr , int size);
    SafeArray(const SafeArray<T>& rhs);

    SafeArray<T>& operator=(const SafeArray<T>& rhs);

    bool operator==(const SafeArray<T>& rhs)const;

    virtual T& operator[](int index);
    virtual const T& operator[](int index) const;


};
#include <cassert>



template <typename T>
SafeArray<T>::SafeArray(int size)
: Array<T>(size)
{

}

template <typename T>
SafeArray<T>::SafeArray(const T *pArr , int size)
: Array<T>(pArr, size)
{

}

template <typename T>
SafeArray<T>::SafeArray(const SafeArray<T>& rhs)
: Array<T>((Array<T>)rhs)
{  //slicing하여 array관련 내용만 남게 타입캐스팅

}
template <typename T>
SafeArray<T>& SafeArray<T>::operator=(const SafeArray<T>& rhs)
{
        if (this != &rhs){
        this->Array<T>::operator=((Array<T>)rhs);
        // safearray 쪽에서 추가된게 있으면 여기에 추가
    }
    return *this;
}

template <typename T>
bool SafeArray<T>::operator==(const SafeArray& rhs)const
{
    return this->Array<T>::operator==((Array<T>)rhs);
}

template <typename T>
T& SafeArray<T>::operator[](int index)
{
    assert(index >= 0 && index < this->size()); //this->Array::size() 에서 Array::생략하여 표기
    return this->Array<T>::operator[](index);
}

template <typename T>
const T& SafeArray<T>::operator[](int index) const
{
    assert(index >= 0 && index < this->size());
    return this->Array<T>::operator[](index);
}
#endif