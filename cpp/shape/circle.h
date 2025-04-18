#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

class Circle : public Shape {
private:
    int radius_;

public:
    Circle(int x, int y, int r);
    // Circle(const Circle& ){ /*memberwise copy*/ }
    virtual ~Circle(){ } //가상 함수를 만들었기에 가상해제로 필요함
    // Circle& operator=(const Circle& ){ /*memberwise copy*/  return *this; }
    // Circle *operator&() {return this;}
    // const Circle* operator&() const {return this};

    virtual double area() const;
    double getCircumference() const;

};

#endif