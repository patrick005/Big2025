#include "circle.h"
#include <cmath> // root 인 sqrt를 사용하기 위함

Circle::Circle(int x, int y, int r)
: Shape(x, y), radius_(r)
{

}

double Circle::area() const{
    return 3.141592 * (radius_ * radius_);
}
double Circle::getCircumference() const{
    return 3.141592 * (radius_ * 2);
}