//functionPointer.c
#include <stdio.h>


int add(int a, int b){
    return a + b;
}

int substract(int a, int b){
    return a - b;
}

int main(void){

    int x = 9;
    int y = 6;
    printf("add(x,y) : %d\n", add(x, y));
    printf("substract(x,y) : %d\n", substract(x, y));

    // 함수포인터 선언
    int (*fp)(int, int);
    //1번 방법
    // fp = &add; // 함수의 주소를 포인터에 연결
    // 2번 방법
    fp = add; // 함수 이름자체가 주소
    printf("add(x,y) : %d\n", (*fp)(x, y));//역참조를 해줘야 위에 그냥 함수를 사용한 것과 동일한 코드
    
    fp = &substract;
    printf("substract(x,y) : %d\n", fp(x, y));

    return 0;
}