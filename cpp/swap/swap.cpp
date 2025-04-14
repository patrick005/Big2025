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
//reference를 활용시엔 함수 overloading을 사용한 중첩은 하지마라. 꼬일 수 있으니 이름을 다르게 줘라
// 사유: 1,2번의 경우 포인터 초기화를 하는 NULL을 0으로 대체가 가능하기에 NULL인지, 정수형 0인지에 대한 오류
// 2,3번의 경우 둘다 포인터이기에 어떤게 우선순위로 들어가는지, 둘다 적용되는지에 대한 문제점

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
