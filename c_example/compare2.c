//compare2.c
//1과 9 사이의 숫자인지 확인해서 맞으면 1 틀리면 0을 프린트 하세요
#include <stdio.h>

int main()
{
    int a;
    int check;
    
    printf("수를 입력하시오 1~9 : ");
    scanf("%d", &a);
    
    check = (1<= a && a <= 9) ;

    printf("1 <= %d <= 9 : %d\n ", a, check);
    return 0;
}