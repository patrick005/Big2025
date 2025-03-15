//sumArrayFunction.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int sumArray(int pArray[], int size);

int main(void){
    int nums[20] = {0};
    srand(time(NULL));
    for(int i = 0; i < 20; ++i){
        nums[i] = rand() % 101;
        printf("%d, ", nums[i]);
    }
    printf("\n");
    //nums에 할당된 메모리 전체 사이즈(80) / 데이터 형식(4)
    int sum = sumArray(nums, sizeof(nums)/sizeof(int));
    printf("sum : %d\n", sum);
    return 0;
}

int sumArray(int pArray[], int size){
    // 20 = sizeof(pArray)/sizeof(int)는 함수가 아닌 상수값(배열 첫번째의 주소값)으로 넘기기에 사용 불가
    //배열을 넘길땐 반드시 주소와 사이즈를 같이 넘겨야한다
    int sum = 0;
    for(int i = 0; i < size; ++i){
        sum += pArray[i];
    }
    return sum;
}