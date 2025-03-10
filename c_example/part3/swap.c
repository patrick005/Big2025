//swap.c
//정렬 - 상호 교환이 불가능하기에 밀어내기식으로 하나씩 바꿈으로써 두 변수의 값을 변경

#include <stdio.h>
 
int main(void){
    int a, b, temp;
    a = 10;
    b = 20;
    
    //swap
    temp = a;
    a = b;
    b = temp;

    printf("a = %d, b = %d\n", a, b);
    return 0;
}
