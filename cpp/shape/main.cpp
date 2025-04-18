#include <iostream>
#include "shape.h"
#include "rectangle.h"
#include "circle.h"

void printShape(const Shape *ps){
    std::cout << "area : " << ps->area() << std::endl;
}

int main() {
    // Shape s;
    /*
    cannot declare variable ‘s1’ to be of abstract type ‘Shape’
    because the following virtual functions are pure within ‘Shape’:
    */
    Shape *ps; // 추상이라 위 방식은 안되지만 포인터로는 가능함
    Rectangle r1(0, 0, 10, 10);
    Circle c1(10, 10, 50);

    Shape *pShapes[5];
    pShapes[0] = new Rectangle(10, 10, 100, 20);
    pShapes[1] = new Circle(50, 50, 20);
    pShapes[2] = new Rectangle(0, 0, 10, 10);
    pShapes[3] = new Circle(100, 10, 50);
    pShapes[4] = new Circle(100, 150, 20);

    for (int i = 0; i < 5; ++i){
        printShape(pShapes[i]);
    }

    for (int i = 0; i < 5; ++i){
        delete pShapes[i];
    }
    

    return 0;
}