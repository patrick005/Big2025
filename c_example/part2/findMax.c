//findMax.c
//10개의 랜덤한 0~100 배열을 만들고 가장 높은 값을 프린트 하세요.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){
    
    int randomNumber [10];
    int max;
    
    //0~100의 범위의 랜덤한 숫자 10개 배열로 저장
    srand((unsigned int)time(NULL));
    for(int i = 0; i < 10; ++i){
        randomNumber[i] = rand() % 101;
        printf("%d, ",randomNumber[i]);
        }
    printf("\n");
    // 저장한 10개의 배열에 대한 더 큰값을 전체 배열 훑을때까지 반복
    max = randomNumber[0];
    for(int i = 0; i<10; ++i){
        if(max < randomNumber[i]){
        max = randomNumber[i];
        }
    }
    printf("max : %d\n",max);
    

    return 0;
}

