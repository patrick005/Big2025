//findValueinArray.c
//10개 짜리 배열을 랜덤으로 0~100 만들어서 int를 하나 scanf로 받는다.
// 같은 원소가 있는지 index가 몇 번째 인지 프린트 하시오
#include <stdio.h>
 
int main(void){
 
    int randomNumber [10];
    int num;
    
    //0~100의 범위의 랜덤한 숫자 10개 배열로 저장
    srand((unsigned int)time(NULL));
    for(int i = 0; i < 10; ++i){
        randomNumber[i] = rand() % 101;
        printf("%d, ",randomNumber[i]);
        }
    printf("\n찾을 값을 입력하시오: ");

    //int값에 대하여 하나 받음
    scanf("%d", &num); 

    //같은 값에 대한 index 출력
    int i;
    for(int i = 0; i < 10; ++i){
        if(num == randomNumber[i]){
            break;
        }
    }

    if (i<10){
        printf("입력한 숫자 %d에 대해 %d에 저장 되어있습니다.\n", num, i);

    }else{
        printf("입력한 숫자 %d에 대해 찾지 못 하였습니다.\n", num);
    }
    return 0;
}