#ifndef ARRAY_H
#define ARRAY_H

// #define ARRAY_SIZE 100
// extern const int ARRAY_SIZE;

class Array
{
private:
    int *pArr_;

protected:
    static const int ARRAY_SIZE;

    int size_;

public:
    static int getDefaultArraySize();

    // Array();
    explicit Array(int size = ARRAY_SIZE);      // explicit 키워드 : 명시적으로만 사용하도록
    Array(const int *pArr, int size);
    Array(const Array& rhs);
    virtual ~Array();

    Array& operator=(const Array& rhs);

    bool operator==(const Array& rhs) const;

    virtual int& operator[](int index);
    virtual const int& operator[](int index) const;

    // Array *operator&() { return this; }
    // const Array *operator&() const { return this; }

    int size() const;
};

#endif