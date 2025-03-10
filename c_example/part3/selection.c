// selection.c
// 0 ~100 랜덤 한 수 20개 프린트.
// 정렬 후 프린트
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

    //selection sorting
    for(int i = 0; i < 20 - 1; ++i){
        for(int j = i + 1; j < 20; ++j){
            if(nums[i]>nums[j]){            //부등호에 따라 오름차순 내림차순
                int temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
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