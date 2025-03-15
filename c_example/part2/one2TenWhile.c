//one2TenWhile.c
//1~10까지 while 로 출력하기

#include <stdio.h>
#include <stdbool.h>

int main(void){

    int i = 0;
    // while (true)
    // {
    //     printf("%d 번 출력합니다.\n", i+1);
    //     ++i;
    //     if(i == 10){
    //         break;
    //     }
    // }
    while (i < 10){
        printf("%d 번 출력합니다.\n", i+1);
        ++i;
    }

    return 0;
}