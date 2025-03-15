//compare.c
//정수를 두 숫자 받아서 크기 관계 0과 1로 프린트 하기
#include <stdio.h>

int main()
{
    int a, b;
    int greater;
    
    printf("두 정수를 입력하시오 : ");
    scanf("%d %d", &a, &b);
    
    greater = a < b;
    printf("greater의 값은 %d이다.\n", greater);
    return 0;
}