//average2022Temp.c

#include <stdio.h>

int main(void){
    double temp[12] = {0};
    for(int i = 0; i < 12; ++i){
        scanf("%lf", &temp[i]);
    }

    double sum = 0;
    for(int i = 0; i < 12; ++i){
        sum += temp[i];
    }

    double average = 0.0;
    // average = sum / 12.0 ;
    
    // 입력 수량에 대한 평균값 측정 (max 12)
    for(int i = 0; i < 12; ++i){
        if(temp[i] != 0){
            average++;
        }
    }
    average = sum / average;


    printf("2022년의 평균 기온은 %.2lf 입니다.\n", average);
    return 0;
}