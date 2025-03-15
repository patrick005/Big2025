//absolute.c
#include <stdio.h>   //pirntf, scanf에 대해 사용할 수 있게 하는 헤더파일
#include <stdbool.h> //true, false에 대해 사용할 수 있게 하는 헤더파일

int main()
{
    //숫자입력
    int num;
    int state;
    printf("숫자를 넣으시오: ");
    scanf("%d", &num);

    //절대값 처리
    if(num<0){
        state = false;
    }else{ 
        state = true;
    }
    num = state ? num : - num;
    //숫자 출력
    printf("주어진 숫자의 절대값은 %d 이다.\n", num);

    return 0;
}