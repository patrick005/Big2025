//one2TenDoWhile.c
//1~10까지 while 로 출력하기

#include <stdio.h>
#include <stdbool.h>

int main(void){

    int i = 0;
    do{
        printf("%d 번 출력합니다.\n", i+1);
        ++i;
    }
    while (i < 10);

    return 0;
}