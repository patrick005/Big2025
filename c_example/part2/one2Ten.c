//one2Ten.c
//1부터 10까지 출력
#include <stdio.h>

int main(void){

    for(int i=0; i<10; ++i){
        printf("출력되는 숫자는 %d 입니다.\n", i+1);
    }
    // for(int i=1; i<=10; ++i){
    //     printf("출력되는 숫자는 %d 입니다.\n", i);
    // }

    return 0;
}