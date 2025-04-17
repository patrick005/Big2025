//testArray.c
#include <stdio.h>
 
int main(void){
    int nums[] = {1, 2, 3, 4, 5};
    int *p;

    p = nums; // p = &nums[0] 배열을 상수처럼쓰면 첫번째 주소의 값

    printf("*p : %d\n", *p);
    printf("*(p + 1): %d\n", *(p + 1));

    int nums1[] = {1, 2, 3, 4, 5};
    int nums2[5];

    //nums2 = nums1; //배열 배열 치환 안됨

    for (int i = 0; i < 5; ++i){
        nums2[i] = nums1[i];
    }
    
    printf("nums2 : ");
    for (int i = 0; i < 5; ++i){
        printf("%d", nums2[i]);
    }
    printf("\n");

    int nums3[] = {1, 2, 3, 4, 5};
    int nums4[] = {1, 2, 3, 4, 5};
    /*
    if (nums3 == nums4){ //배열을 상수처럼 사용시, 배열의 첫번째 값의 주소값을 사용함
        printf("nums3 and nums4 are equal\n");
    }else{
        printf("nums3 and nums4 are not equal\n"); // 이건 조건이 주소의 동일 여부를 확인하기에 무조건 false가 나옴
    }
    */
    int i;
    for (i = 0; i < 5; ++i){
        if (nums3[i] != nums4[i]){
            break;
        }
    }
    if (i == 5){
        printf("nums3 and nums4 are equal\n");
    }else{
        printf("nums3 and nums4 are not equal\n");
    }

    return 0;
}

/*
0100-0600 취침
0600-0700 세면
0730-0750 조식
0800-0850 자습
0900-1730 교육
1730-1800 석식
1800-2300 자습
2300-0100 자습 or 맥주

1년후.. 신입사원
3년후.. 주임달기
5년후.. 결혼? / 대리달기
10년후.. 과장으로 승진이야기 나왔으면...
15년후.. 과장으로 완숙

법의 테두리 안에서는 어떤일이든 오케이?
*/
