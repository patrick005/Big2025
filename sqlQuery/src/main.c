#include "booksql.h"

int main(void){
    MYSQL *conn;
    char *host = "localhost";
    char *user = "myuser";
    char *pass = "0000";
    char *db = "mydb";
    int port = 3306;
    int choice;

    conn = mysql_init(NULL);//db 연결 요청 준비
    if(mysql_real_connect(conn, host, user, pass, db, port, NULL, 0)){
        printf("MySQL 연결 성공\n");
    }else{
        printf("MySQL 연결 실패\n");
        return 1;
    }

    while (true){
        // printf("1번, 2번 고르세요\n");
        print_menu();
        scanf("%d", &choice);
        while(getchar() != '\n');
        switch (choice){
            case SELECT:
                fetch_books(conn);
                break;
            case INSERT:
                add_books(conn);//libmysqlclient.so libmysqlclient.a
                break;
            case DROP:
                delete_books(conn);
                break;
            case ALTER:
                update_books(conn);
                break;
            case QUERY:
                query_books(conn);
                break;
            case EXIT:
                exit_books(conn);
                break;
            default:
                printf("잘못된 접근입니다.\n");
                break;
        }
    }
    mysql_close(conn);
    return 0;
}
//cc -o bookSql bookSql.c -I/usr/include/mysql -L/usr/lib/mysql -lmysqlclient

