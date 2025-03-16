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

// 게임 실행에 대한 main 정리 완
int main(void) {
    // MYSQL 서버 접속
    MYSQL *conn;
    char *host = "localhost";
    char *user = "root";
    char *pass = "0000";
    char *db = "bowling"; // 데이터베이스 이름 변경
    int port = 3306;

    conn = mysql_init(NULL); // db 연결 요청 준비
    if (mysql_real_connect(conn, host, user, pass, db, port, NULL, 0)) {
        printf("MySQL 연결 성공\n");
    } else {
        printf("MySQL 연결 실패\n");
        return 1;
    }

    // 게임 메뉴 실행
    int choice;
    while (true) {
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
            case VISIT:
                visit(conn);
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

// 실행 메뉴판 - 완
void print_menu(void) {
    system("clear");
    printf("=== 볼링 게임 ===\n");
    printf("0. 1인용 게임 시작\n");
    printf("1. 랭킹 확인\n");
    printf("2. 월별 플레이 횟수 확인\n");
    printf("3. 게임 종료\n");
}

// 게임 실행(1인용 기준)
void startgame(MYSQL *conn) {
    int frame;
    int tries[10][2] = {0}; // 각 프레임의 투구 결과를 저장하는 2차원 배열
    int scores[10] = {0}; // 각 프레임의 점수를 저장하는 배열
    int total_score = 0; // 총 점수
    char player_name[40];
    char date[20];

    printf("플레이어 이름을 입력하세요: ");
    scanf("%s", player_name);
    Gametime(date);

    for (frame = 0; frame < 10; frame++) {
        printf("프레임 %d 시작\n", frame + 1);

        // 첫 번째 투구
        printf("첫 번째 투구: ");
        scanf("%d", &tries[frame][0]);
        while(tries[frame][0] < 0 || tries[frame][0] > 10){
            printf("유효하지 않은 값입니다. 다시 입력해주세요:");
            scanf("%d", &tries[frame][0]);
        }
        if (tries[frame][0] == 10) { // 스트라이크
            printf("스트라이크!\n");
            tries[frame][1] = 0; // 두 번째 투구는 생략
        } else {
            // 두 번째 투구
            printf("두 번째 투구: ");
            scanf("%d", &tries[frame][1]);
            while(tries[frame][1] < 0 || tries[frame][1] > (10 - tries[frame][0])){
                printf("유효하지 않은 값입니다. 다시 입력해주세요:");
                scanf("%d", &tries[frame][1]);
            }
            if (tries[frame][0] + tries[frame][1] == 10) { // 스페어
                printf("스페어!\n");
            }
        }

        // 점수 계산
        scores[frame] = tries[frame][0] + tries[frame][1];
        if (frame > 0) {
            if (tries[frame - 1][0] == 10) { // 이전 프레임 스트라이크
                scores[frame - 1] += tries[frame][0]; // 다음 프레임 첫번째 투구만 추가
                if (frame > 1 && tries[frame - 2][0] == 10) { // 연속 스트라이크
                    scores[frame - 2] += tries[frame-1][0]; // 다다음 프레임 첫번째 투구만 추가
                }
            } else if (tries[frame - 1][0] + tries[frame - 1][1] == 10) { // 이전 프레임 스페어
                scores[frame - 1] += tries[frame][0]; // 다음 프레임 첫번째 투구만 추가
            }
        }
        if(frame >= 2 && tries[frame-2][0]==10 && tries[frame-1][0] == 10){
            scores[frame-2] = 30; // 3스트라이크 이상은 30점을 넘을수 없음
        }

        // 프레임별 점수 출력
        printf("|");
        for (int i = 0; i <= frame; i++) {
            printf("%d|%d|", tries[i][0], tries[i][1]);
        }
        for (int i = frame + 1; i < 10; i++) {
            printf("  |  |");
        }
        total_score = 0;
        for(int i = 0; i<=frame; i++){
            total_score += scores[i];
        }
        printf("최종 점수: %d\n", total_score);
    }
    // 최종 점수 계산
    total_score = 0;
    for (int i = 0; i < 10; i++) {
        total_score += scores[i];
    }
    printf("최종 점수: %d\n", total_score);

    // MySQL 데이터 저장
    char query[255];
    sprintf(query, "INSERT INTO score (name, score, date) VALUES ('%s', %d, '%s')", player_name, total_score, date);
    if (mysql_query(conn, query)) {
        printf("쿼리 실패: %s\n", mysql_error(conn));
    }
    // MySQL visit 테이블 업데이트
    char month[8];
    strncpy(month, date, 7);
    month[7] = '\0';
    sprintf(query, "INSERT INTO visit (name, dateMonth, counting) VALUES ('%s', '%s', 1) ON DUPLICATE KEY UPDATE counting = counting + 1", player_name, month);
    if (mysql_query(conn, query)) {
        printf("쿼리 실패: %s\n", mysql_error(conn));
    }
    printf("게임을 종료하시려면 아무 키나 누르세요...\n");
    getchar();
}
    
    // 랭킹 확인
void ranking(MYSQL *conn) {
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[255];
    strcpy(query, "SELECT name, score, date FROM score ORDER BY score DESC");
        // 쿼리 요청
    if (mysql_query(conn, query)) {
        printf("쿼리 실패: %s\n", mysql_error(conn));
        return;
    }
    res = mysql_store_result(conn);
    if (!res) {
        printf("가져오기 실패\n");
        return;
    }
    printf("순위|이름|점수|날짜\n");
    int i = 1;
    while (row = mysql_fetch_row(res)) {
        printf("%d|%s|%s|%s\n", i++, row[0], row[1], row[2]);
    }
    
    mysql_free_result(res);
    printf("메뉴로 돌아가려면 아무 키나 누르세요...\n");
    getchar();
    getchar();
}
// 월별 플레이 횟수 확인
void visit(MYSQL *conn) {
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[255];
    strcpy(query, "SELECT name, dateMonth, counting FROM visit ORDER BY name, dateMonth");
    // 쿼리 요청
    if (mysql_query(conn, query)) {
        printf("쿼리 실패: %s\n", mysql_error(conn));
        return;
    }
    res = mysql_store_result(conn);
    if (!res) {
        printf("가져오기 실패\n");
        return;
    }
    printf("이름|월|플레이 횟수\n");
    while (row = mysql_fetch_row(res)) {
        printf("%s|%s|%s\n", row[0], row[1], row[2]);
    }
    
    mysql_free_result(res);
    printf("메뉴로 돌아가려면 아무 키나 누르세요...\n");
    getchar();
    getchar();
}
// 게임 종료 - 완
void exit_game(MYSQL *conn) {
    exit(0);
}
    
//날짜 관련 작성 요망
int Gametime(char *date){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date, "%d-%02d-%02d", 1900 + tm.tm_year, 1 + tm.tm_mon, tm.tm_mday);
    return 0;
}
        