#include "bowling.h"

//main
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
