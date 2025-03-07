//procScore.c
// n(MAX)개의 숫자를 배열로 만들어서[랜덤] 평균을 소수점 2자리까지 출력


// VLA(variable length array)는 왠만하면 쓰지 마세요.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 5
#define MAXC 100

int main(void){

    int max_input;                        //VLA용 스크립트
    printf("배열의 길이를 넣으세요 : ");    //VLA용 스크립트
    scanf("%d", &max_input);              //VLA용 스크립트
    int scores[max_input];                //VLA용 스크립트(MAX-> max_input)
    int sum = 0;
    double avarage;

    srand((unsigned int)time(NULL));
    for(int i = 0; i < max_input; ++i){     //VLA용 스크립트(MAX-> max_input)
        scores[i] = rand() % (MAXC +1);
        printf("%d ,", scores[i]);
        sum += scores[i];
    }
    printf("\n");
    avarage = (double)sum /max_input;       //VLA용 스크립트(MAX-> max_input)
    printf("평균은 : %.2f 입니다.\n", avarage);


    return 0;
}