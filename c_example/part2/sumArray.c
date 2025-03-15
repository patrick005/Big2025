//sumArray.c
//10짜리 배열을 int로 만들어서 랜덤(0~100) 합을 구해서 프린트하기

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(void){
    
    int randomNumber [10];
    int sum = 0;
    srand(time(NULL));
    for(int i = 0; i < 10; ++i){
        randomNumber[i] = rand() % 101;
        }
    
    for(int i = 0; i<10; ++i){
        sum += randomNumber[i];
        printf("%d, ",randomNumber[i]);
    }
    printf("\n 10개 배열의 총합은 %d 이다. \n,", sum);

    return 0;
}
