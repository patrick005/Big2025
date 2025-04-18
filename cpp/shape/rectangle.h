#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape{
private:
    int width_;
    int height_;

public:
    Rectangle(int x, int y, int w, int h);
    // Rectangle(const Rectangle& ){ /*memberwise copy*/ }
    virtual ~Rectangle(){ } //가상 함수를 만들었기에 가상해제로 필요함
    // Rectangle& operator=(const Rectangle& ){ /*memberwise copy*/  return *this; }
    // Rectangle *operator&() {return this;}
    // const Rectangle* operator&() const {return this};

    virtual double area() const;
    double getDiagonal() const;

};

#endif