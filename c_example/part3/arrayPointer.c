//arrayPointer.c
#include <stdio.h>
 
int main(void){
    int nums[] = {1, 2, 3, 4, 5};
    int *p;

    p = nums;       //이름은 상수로 p = &nums[0]으로 대체해도 된다
                    //하지만 &nums[0] = p로 대체될 순 없다
    for(int i = 0; i < 5; ++i){
        printf("%d 번째 원소는 : %d\n", i, nums[i]);
        printf("%d 번째 원소는 : %d\n", i, p[i]);//배열처럼 선언
        printf("%d 번째 원소는 : %d\n", i, *(p+i));//포인터처럼 선언
    }
    return 0;
}