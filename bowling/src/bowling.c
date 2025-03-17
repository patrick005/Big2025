#include "../include/bowling.h"
#include "../include/bowlingsql.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

static char board[7][50] = {
    "-------------------------------------------",
    "| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10  |",
    "-------------------------------------------",
    "| | | | | | | | | | | | | | | | | | | | | |",
    "-------------------------------------------",
    "|    |    |    |    |    |    |    |    |    |     |",
    "-------------------------------------------",
};

void printBoard(Score *player){
    system(CLEAR_SCREEN);

    printf("\n\n\nPlayer name: %s\n", player->name);
    for (int i = 0; i < 7; i++){
        printf("%s\n", board[i]);
    }
}

void setScore(int frame, int bow, Score *player){
    for (int i = 1; i <= frame; i++){
        for (int j = 1; j <= 2; j++){
            board[3][1 + (i - 1) * 4 + (j - 1) * 2] = ' ';
        }
    }
    if (frame == 10 && bow == 1){
        board[3][1 + (frame - 1) * 4] = ' ';
        board[3][1 + (frame - 1) * 4 + 2] = ' ';
        board[3][1 + (frame - 1) * 4 + 4] = ' ';
    }
    for (int i = 1; i <= frame; i++){
        for (int j = 1; j <= 2; j++){
            if (i == frame && bow == 1 && j == 2 && i <= 9)
                break;
            if (player->score[i][j] == 10 && j == 1){
                board[3][1 + (i - 1) * 4 + (j - 1) * 2] = 'X';
            }else if(player->score[i][j] == 10 && i == 10 && j == 2)
            {
                board[3][1 + (i - 1) * 4 + (j - 1) * 2] = 'X';
            }
            else if (player->score[i][j] + player->score[i][j - 1] == 10 && j == 2 && player->score[i][j - 1] != 10){
                board[3][1 + (i - 1) * 4 + (j - 1) * 2] = '/';
            }else if (player->score[i][j] + player->score[i][j - 1] < 10){
                board[3][1 + (i - 1) * 4 + (j - 1) * 2] = player->score[i][j] + '0';
            }
        }
    }
    if (frame == 10 && bow == 3){
        if (player->score[10][3] == 10){
            board[3][1 + (10 - 1) * 4 + (3 - 1) * 2] = 'X';
        }else{
            board[3][1 + (10 - 1) * 4 + (3 - 1) * 2] = player->score[10][3] + '0';
        }
    }
}

void setFrameScore(int frame, Score *player){
    char buf[4];
    sprintf(buf, "%3d", player->frameScore[frame]);
    strncpy(board[5] + (frame - 1) * 4 + 1, buf, 3);
}

void waitEnter(void){
    printf("엔터를 쳐 주세요....\n");
    while (getchar() != '\n')
        ;
}

// 게임 실행 함수
void runGame(MySQLConnection *mysql){
    Score player;
    char name[10];

    // 시작 시 화면 지우기
    system(CLEAR_SCREEN);

    printf("볼링 게임을 시작합니다!\n");
    printf("플레이어 이름을 입력하세요 (최대 9글자): ");
    scanf("%9s%*c", name);

    // 점수 초기화
    initScore(&player, name);

    // 보드 출력
    printBoard(&player);

    // 1-9 프레임 진행
    for (int i = 1; i <= 9; i++){
        playGame(&player, i);
    }

    // 10 프레임 진행 (특별 규칙 적용)
    playGame10Frame(&player);

    // 종료 시 화면 지우고 최종 결과 표시
    system(CLEAR_SCREEN);
    printBoard(&player);
    printf("\n게임이 종료되었습니다!\n");
    printf("최종 점수: %d\n", player.frameScore[10]);

    // MySQL에 점수 저장
    if (mysql->conn != NULL){
        saveScore(mysql, player.name, player.frameScore[10]);
        updateMonthlyStats(mysql);
    }
    waitEnter();
}




