//bubble.c


#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

int main(void){

    int nums[20] = {0};
    srand(time(NULL));
    for(int i = 0; i < 20; ++i){
        nums[i] = rand() % 101;
    }
    for(int i = 0; i < 20; ++i){
        printf("%d, ", nums[i]);
    }
    printf("\n");

    //bubble sorting
    for(int i = 20 - 1; i >= 1; --i){   //i는 각 스텝의 비교할 횟수
        for(int j = 0; j < i; ++j){
            if(nums[j]>nums[i]){
                int temp = nums[j];
                nums[j] = nums[j+1];
                nums[j+1]= temp;
            }
        }
    }
    





    //정렬된 값 출력
    for(int i = 0; i < 20; ++i){
        printf("%d, ", nums[i]);
    }
    printf("\n");
    return 0;
}