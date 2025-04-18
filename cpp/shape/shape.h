#ifndef SHAPE_H
#define SHAPE_H

class Shape{        //Abstract Base Class 추상 기저(기반) 클래스 --> 순수 가상 함수를 한개 이상 갖는 클래스를 지칭
// private:

protected:
    int x_;
    int y_;

public:
    Shape();
    Shape(int x, int y);
    // Shape(const Shape& ){ /*memberwise copy*/ }
    virtual ~Shape(){}; //가상 함수를 만들었기에 가상해제로 필요함
    // Shape& operator=(const Shape& ){ /*memberwise copy*/  return *this; }
    // Shape *operator&() {return this;}
    // const Shape* operator&() const {return this};

    void move(int x, int y);
    virtual double area() const = 0;        // can't be implemented. --> pure virtual func.
    // 여기서 넓이를 지정할 방법이 없어서 순수 가상함수로 만듬

};

#endif