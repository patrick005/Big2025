//qsort.c

#include <stdio.h>
#include <stdlib.h> //qsort 포함
#include <time.h> 

int compare(const void *a, const void *b){
    return (*(int *)a - *(int *)b);
}
// a-b 오름차순, b-a 내림차순

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

    //q sorting
    qsort(nums, 20, sizeof(nums[0]), compare);

    //정렬된 값 출력
    for(int i = 0; i < 20; ++i){
        printf("%d, ", nums[i]);
    }
    printf("\n");
    return 0;
}