#include "rectangle.h"
#include <cmath> // root 인 sqrt를 사용하기 위함

Rectangle::Rectangle(int x, int y, int w, int h)
: Shape(x, y), width_(w), height_(h)
{

}

double Rectangle::area() const{
    return width_ * height_;
}
double Rectangle::getDiagonal() const{
    return sqrt(width_*width_ + height_ * height_); // sqrt는 루트를 구현한 함수
}