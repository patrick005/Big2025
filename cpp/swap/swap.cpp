#include <iostream>

void swap(int a, int b){ //ver. fail 함수내에서 교체는하지만 메인에 반영이 안 되는 구조
    int tmp = a;
    a = b;
    b = tmp;
}
void swap2(int *pa, int *pb){ //ver. pointer
    int tmp = *pa;
    *pa = *pb;
    *pb = tmp;
}
void swap3(int &ra, int &rb){ //ver. reference
    int tmp = ra;
    ra = rb;
    rb = tmp;
}

int main(){
    int a = 100;
    int b = 200;

    std::cout << "a: " << a << '\t'<< "b: " << b << std::endl;
    // swap(a,b);
    // swap2(&a,&b);
    swap3(a,b);
    
    std::cout << "a: " << a << '\t'<< "b: " << b << std::endl;

    return 0;
}
