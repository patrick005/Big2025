#ifndef BOUNDARRAY_H
#define BOUNDARRAY_H

#include "safeArray.h"

class BoundArray : public SafeArray{
private:
    int low_;
    int up_;

public:
    // // SafeArray(){}
    // // SafeArray(const SafeArray& ){ /*memberwise copy*/ }
    // // ~SafeArray(){}
    // // SafeArray& operator=(const SafeArray& ){ /*memberwise copy*/ }
    // // SafeArray *operator&() {return this;}
    // // const SafeArray* operator&() const {return this};

    // explicit SafeArray(int size = Array::getDefaultArraySize());
    // SafeArray(const int *pArr , int size);
    // SafeArray(const SafeArray& rhs);
    // // ~SafeArray(){}
    // SafeArray& operator=(const SafeArray& rhs);

    // bool operator==(const SafeArray& rhs)const;

    // virtual int& operator[](int index);
    // virtual const int& operator[](int index) const;
    // // int size(); // array쪽에 이미 있기에 가져오면 됨 -> Array::size() is inherited by public

    void upper();
    void lower();

};

#endif