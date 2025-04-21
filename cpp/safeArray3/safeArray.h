#ifndef SAFE_ARRAY_H
#define SAFE_ARRAY_H
#include "array.h"
// 상속
class SafeArray : public Array
{
private:

public:
    explicit SafeArray(int size = Array::ARRAY_SIZE);
    SafeArray(const int* pArr, int size);
    SafeArray(const SafeArray& rhs);
    // virtual ~SafeArray() { }
    SafeArray& operator=(const SafeArray& rhs);

    bool operator==(const SafeArray& rhs) const;

    virtual int& operator[] (int index);
    virtual const int& operator[] (int index) const;

    // SafeArray *operator&() { return this; }
    // const SafeArray *operator&() const { return this; }

};

#endif