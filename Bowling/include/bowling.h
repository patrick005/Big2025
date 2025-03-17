#include <mysql.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

// cc -o bowling bowling.c -I/usr/include/mysql -L/usr/lib/mysql -lmysqlclient

typedef struct {
    char player[40];
    int score;
    int count;
} Bowling;

enum menu {
    START,  // 1인용 시작
    RANKING, // 기록된 플레이 내역 확인
    VISIT, // 월별 플레이 횟수 확인
    EXIT    // 게임 종료
};

void startgame(MYSQL *conn);    // 게임 실행
void ranking(MYSQL *conn);      // 랭킹 확인
void visit(MYSQL *conn);        // 월별 플레이 횟수 확인
void exit_game(MYSQL *conn);    // 게임 종료
void print_menu(void);  // 실행 메뉴판
int Gametime(char *date); //날짜 반환
