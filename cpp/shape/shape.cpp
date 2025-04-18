#include "shape.h"

Shape::Shape()
: x_(0), y_(0)
{

}
Shape::Shape(int x, int y)
: x_(x), y_(y)
{

}

void Shape::move(int x, int y){
    x_ += x;
    y_ += y;
}
