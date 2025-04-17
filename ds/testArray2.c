//testArray.c
#include <stdio.h>


int sumArray(const int *pArr, int size){
    int sum = 0;
    for (int i = 0; i < size; ++i){
        sum += pArr[i];
    }
    return sum;
}

int sumArray2(int arr[]){
// int sumArray2(int arr[10]){ -> 숫자는 무시된다, arr은 포인터이다(인자에서 대괄호는 배열이 아니라 포인터이기 때문)
    int sum = 0;
    for (int i = 0; i < 10; ++i){
    // for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i){ // 운영체제마다 다르고 헷갈리는 상황이라 동적으로 적용할거 아니면 쓰지마라
        // sum += arr[i];
        sum += *arr++;
    }
    return sum;
}

int main(void){
    int nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // int sum = sumArray(nums, 10);
    // int sum = sumArray(nums+5, 5);
    int sum = sumArray2(nums);
    printf("sum = %d\n", sum);
    
    return 0;
}
