//functionSum.c
//매개변수 두개를 int로 받아서 더해서 리턴하는 함수

#include <stdio.h>


int sum(int a, int b);

int main(void){

    int a= 10, b = 20;
    int result;

    result = sum(a,b);
    printf("%d + %d = %d 입니다.\n",a, b, result);

    return 0;
}

int sum(int a, int b){
    int temp;
    temp = a + b;
    return temp;

}
