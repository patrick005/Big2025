//baseball.c
// 숫자 3개를 만드시오[랜덤](서로 다른 숫자 0 ~ 9)
// 숫자 3개를 입력받으시오.
// 위치와 숫자가 같으면 strike + 1 
// 위치가 다르지만 숫자가 같으면 ball +1
// 모든 데이터의 위치와 숫자가 동일하면 성공
// 시도 횟수를 출력하는 프로그램을 만드세요

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 3                                   //시스템상 제공하는 숫자의 개수 제한
#define MAXC 100

int main(void){

    int ball_input[3] = {0};                        //입력받는 공 숫자 3개 배열
    int ball_sys[3];                                //시스템 출력 공 숫자 3개 배열
    int temp;                                       //중복검사
    int count = 0;                                  //시도 횟수
    int strike = 0;                                 //스트라이크 횟수([i], i 같을때)
    int ball = 0;                                   //볼 횟수        ([i] 같을때)

    printf("0~9까지의 숫자 중 3개를 넣으세요 : ");
    for(int i = 0; i < 10; ++i){
        scanf("%d", &ball_input[i]);              //공 3개에 대해 입력 
    }

    srand((unsigned int)time(NULL));
    for(int i = 0; i < MAX; ++i){
        ball_sys[i] = rand() % 9;        //시스템 출력 공 3개
    }
    printf("\n");

    //배열간 비교 및 추출
    for(int i = 2; i <= ball_input[0]; i++){
        int count = 0;

        for(int j = 2; j <= i; j++){

            if(i % j == 0){
                count ++;
            }else
                continue;

        }
        if(count == 1){
            //result++;
        }
    }

    return 0;
}