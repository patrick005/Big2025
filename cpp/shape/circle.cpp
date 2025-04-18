#include "circle.h"
#include <cmath> // root 인 sqrt를 사용하기 위함

Circle::Circle(int x, int y, int r)
: Shape(x, y), radius_(r)
{

}

double Circle::area() const{
    return radius_ * radius_ * 3.14;
}
double Circle::getCircumference() const{
    return radius_ * 2 * 3.14;
}