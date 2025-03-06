//oddeven.c
//짝수 홀수 구별하기 홀수면 1, 짝수면 0
#include <stdio.h>

int main()
{
    int a;
        
    printf("수를 입력하시오 : ");
    scanf("%d", &a);
    
    int isOdd;
    isOdd = a % 2 ;
    // isOdd = ( a % 2 ==1);
    printf("입력한 수 : %d \t 홀수인가 : %d\n", a, isOdd);
    return 0;
}