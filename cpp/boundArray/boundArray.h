#ifndef BOUNDARRAY_H
#define BOUNDARRAY_H

#include "safeArray.h"

class BoundArray : public SafeArray{
private:
    int low_;

public:
    // // SafeArray(){}
    // // SafeArray(const SafeArray& ){ /*memberwise copy*/ }
    // // ~SafeArray(){}
    // // SafeArray& operator=(const SafeArray& ){ /*memberwise copy*/ }
    // // SafeArray *operator&() {return this;}
    // // const SafeArray* operator&() const {return this};

    explicit BoundArray(int size = SafeArray::getDefaultArraySize());    //-> 할아버지에 defaultsize 명시 되어있음
    // 하한(low)과 상한 직전 값(high)으로 초기화하는 생성자: 크기는 high - low
    BoundArray(int low, int upper);
    BoundArray(const BoundArray& rhs);
    virtual ~BoundArray();
    
    BoundArray& operator=(const BoundArray& rhs);
    bool operator==(const BoundArray& rhs)const;
    
    int& operator[](int index);
    const int& operator[](int index) const;

    int upper() const;
    int lower() const;

};

#endif