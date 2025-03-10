// baseball.c
// 숫자 3개를 만드시오[랜덤](서로 다른 숫자 0 ~ 9)
// 숫자 3개를 입력받으시오.
// 위치와 숫자가 같으면 strike + 1 
// 위치가 다르지만 숫자가 같으면 ball +1
// 모든 데이터의 위치와 숫자가 동일하면 성공
// 시도 횟수를 출력하는 프로그램을 만드세요

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){

    int ball_input[3] = {0};                        //입력받는 공 숫자 3개 배열
    int ball_sys[3] = {0};                          //시스템 출력 공 숫자 3개 배열
    int temp;                                       //중복검사
    int count = 0;                                  //시도 횟수
    int strike = 0;                                 //스트라이크 횟수([i], i 같을때)
    int ball = 0;                                   //볼 횟수        ([i] 같을때)

    srand((unsigned int)time(NULL));                //시스템 출력 공 3개
    for(int i = 0; i < 3; ++i){
        ball_sys[i] = rand() % 10;
        for (int j = 0; j < i; j++){
			if (ball_sys[i] == ball_sys[j]){
				i--;
				break;
			}
		}
    }
    printf("\n");

    while (strike != 3) {						
        START:
            printf("0~9까지의 숫자 중 3개를 넣으세요 : ");      //사용자 입력 공 3개
            scanf("%d", &temp);
            strike = 0;
            ball = 0;

            ball_input[0] = temp / 100 % 10;
            ball_input[1] = temp / 10 % 10;
            ball_input[2] = temp % 10;

            if (temp < 0 || temp > 999){                        //입력값에 대한 유효성 검사
                printf("\n 유효한 값이 아닙니다.\n");
                goto START;
            }
    
            for (int i = 0; i < 3; i++){                        //입력값에 대한 중복성 검사
                for (int j = 0; j < i; j++){
                    if (ball_input[i] == ball_input[j]){
                        printf("\n중복된 숫자가 존재합니다.\n");
                        goto START;
                    }
                    continue;
                }
            }
    
            for (int i = 0; i < 3; i++){                        //입력값에 대한 판독
                for (int j = 0; j < 3; j++){
                    if (ball_sys[i] == ball_input[j]){
                        if (i == j){
                             strike++;
                        }else{
                            ball++;
                            break;
                        }
                    }
                }
            }

            count++;
            printf("strike:%d\nball:%d", strike, ball);
            printf("\n");
        }
    printf("승리하셨습니다. 총 시도 횟수는 %d회 입니다.\n", count);
    return 0;
}