#include <mysql.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

// MySQL 데이터베이스 정보
#define DB_HOST "localhost"
#define DB_USER "myuser"
#define DB_PASS "0000"
#define DB_NAME "bowling"
#define DB_PORT 3306

typedef struct{
    char player[40];
    int score;
    int count;
} Bowling;

enum menu {
    START,   // 1인용 시작 
    RANKING, // 기록된 플레이 내역 확인
    EXIT     // 게임 종료
};

void startgame(MYSQL *conn);    // 게임 실행
void ranking(MYSQL *conn);      // 게임 내역 확인
void exit_game(MYSQL *conn);    // 게임 종료
void print_menu(void);          // 실행 메뉴판
void save_score(MYSQL *conn, const char *name, int final_score); // 점수 저장
void update_visit(MYSQL *conn, const char *name); // 방문 기록 업데이트
void print_scoreboard(int scores[10][2], int frame);

int main(void) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT, NULL, 0)) {
        printf("MySQL 연결 실패\n");
        return 1;
    }
    printf("MySQL 연결 성공\n");

    int choice;
    while (1) {
        print_menu();
        scanf("%d", &choice);
        while (getchar() != '\n');
        switch (choice) {
            case START:
                startgame(conn);
                break;
            case RANKING:
                ranking(conn);
                break;
            case EXIT:
                exit_game(conn);
                break;
            default:
                printf("잘못된 접근입니다.\n");
                break;
        }
    }
    mysql_close(conn);
    return 0;
}

void print_menu(void) {
    system("clear");
    printf("=== 볼링 게임 ===\n");
    printf("0. 1인용 게임 시작\n");
    printf("1. 랭킹 확인\n");
    printf("2. 게임 종료\n");
}

void startgame(MYSQL *conn) {
    char player[40];
    printf("플레이어 이름을 입력하세요: ");
    scanf("%39s", player);

    int scores[10][2] = {0};
    int total_score = 0;
    int bonus[10] = {0};

    for (int frame = 0; frame < 10; frame++) {
        printf("%d 프레임 - 첫 번째 투구 (0-10): ", frame + 1);
        scanf("%d", &scores[frame][0]);

        if (scores[frame][0] == 10) { // 스트라이크
            printf("스트라이크!\n");
            scores[frame][1] = -1; // 두 번째 투구 없음
            if (frame > 0) bonus[frame - 1] += scores[frame][0];
            if (frame > 1 && scores[frame - 1][0] == 10) bonus[frame - 2] += scores[frame][0];
        } else {
            printf("%d 핀 남음, 두 번째 투구 (0-%d): ", 10 - scores[frame][0], 10 - scores[frame][0]);
            scanf("%d", &scores[frame][1]);
            if (scores[frame][0] + scores[frame][1] == 10) {
                printf("스페어!\n");
                if (frame > 0) bonus[frame - 1] += scores[frame][0];
            }
        }
        total_score += scores[frame][0] + (scores[frame][1] == -1 ? 0 : scores[frame][1]) + bonus[frame];
        print_scoreboard(scores, frame + 1);
    }
    save_score(conn, player, total_score);
    update_visit(conn, player);
}

void print_scoreboard(int scores[10][2], int frame) {
    printf("| ");
    for (int i = 0; i < 10; i++) {
        if (i < frame) {
            printf("%2d | %2d | ", scores[i][0], scores[i][1] == -1 ? 0 : scores[i][1]);
        } else {
            printf("   |    | ");
        }
    }
    printf("Final: %d\n", frame == 10 ? scores[9][0] + scores[9][1] : 0);
}

void save_score(MYSQL *conn, const char *name, int final_score) {
    char query[256];
    sprintf(query, "INSERT INTO score (name, score, date) VALUES ('%s', %d, CURDATE())", name, final_score);
    if (mysql_query(conn, query)) {
        printf("점수 저장 실패\n");
    }
}

void update_visit(MYSQL *conn, const char *name) {
    char query[256];
    sprintf(query, "INSERT INTO visit (name, counting, dateMonth) VALUES ('%s', 1, DATE_FORMAT(NOW(), '%%Y-%%m')) ON DUPLICATE KEY UPDATE counting = counting + 1", name);
    if (mysql_query(conn, query)) {
        printf("방문 기록 업데이트 실패\n");
    }
}

void ranking(MYSQL *conn) {
    MYSQL_RES *res;
    MYSQL_ROW row;
    if (mysql_query(conn, "SELECT name, score, date FROM score ORDER BY score DESC")) {
        printf("랭킹 조회 실패\n");
        return;
    }
    res = mysql_store_result(conn);
    if (!res) {
        printf("데이터 가져오기 실패\n");
        return;
    }
    printf("이름\t점수\t날짜\n");
    while ((row = mysql_fetch_row(res))) {
        printf("%s\t%s\t%s\n", row[0], row[1], row[2]);
    }
    mysql_free_result(res);
}

void exit_game(MYSQL *conn) {
    exit(0);
}
