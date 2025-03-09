//test
#include <stdio.h>
#include <stdlib.h>							//srand()를 위해
#include <time.h>							//시간을 시드로 받기 위해

int main(void){
	char answer[4] = { 0,};						//랜덤 변수
	char user_input[4] = { 0, };				//유저 인풋
	int temp = 0, 
		count = 0, 
		rike = 0,
		ball = 0;//input을 저장하기 위한 temp, 시행횟수 count, 게임을 위한 strike, ball


	srand((unsigned int)time(NULL));			//랜덤 난수 생성
	for (int i = 0; i < 4; i++){
		answer[i] = rand() % 10;
		for (int check = 0; check < i; check++){
			if (answer[i] == answer[check]){
				i--;
				break;
			}
		}
	}

	while (strike != 4) {						//STRIKE가 4일시 BREAK
	ERROR:
		printf("Write you answer\n");
		scanf_s("%d", &temp);

		user_input[0] = temp / 1000;
		user_input[1] = temp / 100 % 10;
		user_input[2] = temp / 10 % 10;
		user_input[3] = temp % 10;
//0~9999사이 인풋이 아닐시
		if (temp < 0 || temp > 9999){
			printf("Give range of 0000~9999 input\n");
			goto ERROR;
		}
//중복된 인풋이 존재할 시
		for (int i = 0; i < 4; i++){
			for (int check = 0; check < i; check++){
				if (user_input[i] == user_input[check]){
					printf("same number input!\n");
					goto ERROR;
				}
			}
		}

		strike = 0;	ball = 0;					//Strike, Ball 초기화
//정답확인
		for (int ans_i = 0; ans_i < 4; ans_i++){
			for (int inp_i = 0; inp_i < 4; inp_i++){
				if (answer[ans_i] == user_input[inp_i]){
					if (ans_i == inp_i){
						 strike++;
					}else{
						ball++;
						break;
					}
				}
			}
		}

		count++;									//정답출력
		printf("%d.", count);						//Strike,Ball 출력

		for (int i = 0; i < 4; i++){
			printf("%d", user_input[i]);
		}
		printf("	s:%d	b:%d", strike, ball);
		printf("\n");
	}
	printf("you win this game!");				//승리메세지
	return 0;
}