#include <stdio.h>

int main()
{
    int man, woman;
    double sum, manRate, womanRate;

    //입력받는 코드
    printf("남자의 수를 입력하시오 : ");
    scanf("%d", &man);
    printf("여자의 수를 입력하시오 : ");
    scanf("%d", &woman);
    //연산하는 코드
    sum = man + woman;
    manRate = man / sum * 100;
    womanRate = woman / sum * 100;

    printf("남자의 수는 %d명이고 여자의 수는 %d이다.\n", man, woman);
    printf("총 수는 %.f명\n남자의 비율은 %.2f%%\n여자의 비율은 %.2f%%\n", sum, manRate, womanRate);
    
    return 0;
}