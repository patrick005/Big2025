//score.c
#include "../include/bowling.h"
#include "../include/bowlingsql.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// 운영체제 확인을 위한 매크로 추가
#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif


// 점수 정보 초기화 함수
void initScore(Score *player, const char iname[]){
    strcpy(player->name, iname);
    memset(player->score, 0, sizeof(player->score));
    memset(player->frameScore, 0, sizeof(player->frameScore));
}

// 프레임 점수 계산 함수
void calScore(int *frameScore, const int (*score)[3]){
    for (int i = 1; i <= 10; i++){
        frameScore[i] = frameScore[i - 1];
        if (score[i][1] == 10){
            frameScore[i] += 10 + score[i + 1][1] + score[i + 2][1]; // 스트라이크
        }else if (score[i][1] + score[i][2] == 10){
            frameScore[i] += 10 + score[i + 1][1];  // 스페어
        }else{
            frameScore[i] += score[i][1] + score[i][2];
        }
    }
}

// 유효한 점수 입력 함수
int getValidScore(int frame, int bow, int prevScore){
    int score;
    while (1){
        printf("%d프레임 %d번째 투구 점수 입력: ", frame, bow);
        scanf("%d", &score);
        if (score >= 0 && score <= 10){
            if (bow == 2 && prevScore + score > 10){
                printf("잘못된 입력입니다. 다시 입력하세요.\n");
            }else{
                break;
            }
        }else{
            printf("잘못된 입력입니다. 다시 입력하세요.\n");
        }
    }
    return score;
}

// 게임 플레이 함수
void playGame(Score *player, int i){
    player->score[i][1] = getValidScore(i, 1, 0);
    setScore(i, 1, player);
    printBoard(player);

    if (player->score[i][1] != 10){
        player->score[i][2] = getValidScore(i, 2, player->score[i][1]);
        setScore(i, 2, player);
        printBoard(player);
    }
    calScore(player->frameScore, (const int (*)[3])player->score);
    setFrameScore(i, player);
    printBoard(player);
}
// 10 프레임 게임 플레이 함수
void playGame10Frame(Score *player){
    player->score[10][1] = getValidScore(10, 1, 0);
    setScore(10, 1, player);
    printBoard(player);

    if (player->score[10][1] == 10){
        player->score[10][2] = getValidScore(10, 2, 0);
        setScore(10, 2, player);
        printBoard(player);

        if (player->score[10][2] == 10){
            player->score[10][3] = getValidScore(10, 3, 0);
            setScore(10, 3, player);
            printBoard(player);
        }else{
            player->score[10][3] = getValidScore(10, 3, player->score[10][2]);
            setScore(10, 3, player);
            printBoard(player);
        }
    }else if (player->score[10][1] + player->score[10][2] == 10){
        player->score[10][3] = getValidScore(10, 3, 0);
        setScore(10, 3, player);
        printBoard(player);
    }else{
        player->score[10][2] = getValidScore(10, 2, player->score[10][1]);
        setScore(10, 2, player);
        printBoard(player);
    }
    calScore(player->frameScore, (const int (*)[3])player->score);
    setFrameScore(10, player);
    printBoard(player);
}

// 메뉴 출력 함수
void printMenu(){
    system(CLEAR_SCREEN);
    printf("=== 볼링 게임 시스템 ===\n");
    printf("1. 게임 플레이\n");
    printf("2. 내 기록 보기\n");
    printf("3. 최고 점수 보기\n");
    printf("4. 월별 통계 보기\n"); 
    printf("0. 종료\n");
    printf("선택: ");
}
