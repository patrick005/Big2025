//enumExample.c
#include <stdio.h>

enum season // 옵션이나 스위치문 메뉴 관련 코드에서 많이 쓰임.
{
    SPRING = 1, // int -> 0
    SUMMER = 2, // int -> 1
    FALL = 4,   // int -> 2
    WINTER = 8  // int -> 3
};
// #define SPRING 0
// #define SUMMER 1
// ...
// ss = SPRING | SUMMER;

int main(void){
    enum season ss;
    char *pc = NULL;

    ss = SPRING;
    switch (ss){
        case SPRING: // 가시성...
            pc = "inline";
            break;
        case SUMMER:
            pc = "swimming";
            break;
        case FALL:
            pc = "trip";
            break;
        case WINTER:
            pc = "skiing";
            break;
    }
    printf("나의 레저 활동 => %s\n", pc);
    return 0;
}