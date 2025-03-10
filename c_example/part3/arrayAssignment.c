//arrayAssignment.c

#include <stdio.h>
 
int main(void){
    int nums1[] = {1, 2, 3, 4, 5};
    int nums2[5];

    //nums2 = nums1; // 이처럼 쓰면 안된다는 것을 보여주기 위함
    //상수가 앞에 나올순 없음, 함수명도 상수 취급임

    //deep copy 하는 방법, 다른메모리에 다 복사한다
    for(int i = 0; i < 5; ++i){
        nums2[i] = nums1[i];     
    }
    printf("nums1 의 주소값 %p\n", nums1);
    printf("nums2 의 주소값 %p\n", nums2);
    // 서로 독립적인 메모리이다.
    nums2[3] = 14;
    //shallow copy, 메모리를 공유하는 방법
    int *nums3;
    nums3 = nums1;
    printf("nums3 의 주소값 %p\n", nums3);
    nums3[2] = 23;

    for(int i = 0; i < 5; ++i){
        printf("----------------\n");
        printf("nums1 %d : %d, \n", i , nums1[i]);
        printf("nums2 %d : %d, \n", i , nums2[i]);
        printf("nums3 %d : %d, \n", i , nums3[i]);
    }
    
    
    return 0;
}