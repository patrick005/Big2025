
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/bowling.h"
#include "../include/bowlingsql.h"

// 사용자 입력 대기 함수 추가
void waitEnter(void);

// 게임 로직 및 점수 계산 관련 함수
void initScore(Score *player, const char iname[]);
void calScore(int *frameScore, const int (*score)[3]);
int getValidScore(int frame, int bow, int prevScore);
void playGame(Score *player, int i);
void playGame10Frame(Score *player);

int main(){
    int choice;
    char username[50];
    MySQLConnection mysql = {0};
    bool dbConnected = false;

    // MySQL 연결 시도
    dbConnected = initMySQL(&mysql);
    if (!dbConnected){
        printf("경고: 데이터베이스 연결 실패. 점수가 저장되지 않습니다.\n");
        waitEnter();
    }

    while (true){
        printMenu();
        scanf("%d%*c", &choice);

        switch (choice){
        case PLAY_GAME:
            runGame(&mysql);
            break;

        case VIEW_HISTORY:
            system(CLEAR_SCREEN);
            if (!dbConnected){
                printf("데이터베이스 연결이 필요합니다.\n");
            }else{
                printf("사용자 이름을 입력하세요: ");
                scanf("%49s%*c", username);
                printUserHistory(&mysql, username);
            }
            waitEnter();
            break;

        case TOP_SCORES:
            system(CLEAR_SCREEN);
            if (!dbConnected){
                printf("데이터베이스 연결이 필요합니다.\n");
            }else{
                printTopScores(&mysql, 10); // 상위 10개 점수 표시
            }
            waitEnter();
            break;

        case MONTHLY_STATS: 
            system(CLEAR_SCREEN);
            if (!dbConnected){
                printf("데이터베이스 연결이 필요합니다.\n");
            }else{
                printf("사용자 이름을 입력하세요 (모든 사용자 통계를 보려면 그냥 Enter): ");
                // 사용자 입력 받기
                if (fgets(username, sizeof(username), stdin)){
                    // 개행 문자 제거
                    username[strcspn(username, "\n")] = 0;

                    // 월별 통계 업데이트 및 출력
                    updateMonthlyStats(&mysql);

                    // 빈 문자열이면 NULL 전달
                    if (username[0] == '\0')
                        printMonthlyStats(&mysql, NULL);
                    else
                        printMonthlyStats(&mysql, username);
                }
            }
            waitEnter();
            break;

        case EXIT:
            if (dbConnected){
                closeMySQL(&mysql);
            }
            printf("프로그램을 종료합니다. 감사합니다!\n");
            return 0;

        default:
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
            break;
        }
    }
    return 0;
}


