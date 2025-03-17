#ifndef BOWLING_H
#define BOWLING_H

// 메뉴 상수 정의를 enum으로 변경
typedef enum
{
    PLAY_GAME = 1,
    VIEW_HISTORY,
    TOP_SCORES,
    MONTHLY_STATS, // 새 메뉴 옵션
    EXIT = 0
} MenuOption;


typedef struct
{
    int score[12][3];
    int frameScore[11];
    char name[10];
} Score;


// 보드 출력 관련 함수
void printBoard(Score *player);
void setScore(int frame, int bow, Score *player);
void setFrameScore(int frame, Score *player);



#endif