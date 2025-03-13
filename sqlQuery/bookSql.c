#include <mysql.h>
#include <stdio.h>
#include <string.h>
//sudo apt install libmysql++*
//mysql사용을 위한 설치
//dpkg -L libmysqlclient-dev | grep mysql.h
//위치확인
//.vscode/c_cpp_properties.json에서 Path 설정
//외부라이브러리라 3가지를 명시해야한다
//cc -o bookSql bookSql.c -I/usr/include/mysql -L/usr/lib/mysql -lmysqlclient
//-I-L-l

//libmysqlclient.so libmysqlclient.a -->.so동적라이브러리 자체 내장

typedef struct{
    int bookid;
    char bookname[40];
    char publisher[40];
    int price;
}Book;

enum menu{
    SELECT, 
    INSERT, 
    DROP, 
    ALTER, 
    QUERY
};

void fetch_books(MYSQL *conn);
void add_books(MYSQL *conn);
void delete_books(MYSQL *conn);
void update_books(MYSQL *conn);
void query_books(MYSQL *conn);
void print_menu(void);

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
        }
    }
    mysql_close(conn);
    return 0;
}
//cc -o bookSql bookSql.c -I/usr/include/mysql -L/usr/lib/mysql -lmysqlclient

void print_menu(void){

    system("clear");
    printf("=== 도서 관리 시스템 ===\n");
    printf("0. 도서 조회\n");
    printf("1. 도서 추가\n");
    printf("2. 도서 삭제\n");
    printf("3. 도서 변경\n");
    printf("4. 쿼리 입력\n");
}

void fetch_books(MYSQL *conn){
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[255];
    strcpy(query, "select * from Book");

    // 쿼리 요청
    if (mysql_query(conn, query)){
        printf("쿼리 실패");
        return;
    }
    res = mysql_store_result(conn);
    if (!res){
        printf("가져오기 실패!\n");
        return;
    }
    Book *pBook;
    pBook = (Book *)malloc(sizeof(Book));
    int i = 0;
    // 데이터 베이스의 정보를 구조체에 저장 - ORM
    while (row = mysql_fetch_row(res)){
        (pBook + i)->bookid = atoi(row[0]);
        strcpy((pBook + i)->bookname, row[1]);
        strcpy((pBook + i)->publisher, row[2]);
        (pBook + i)->price = atoi(row[3]);
        ++i;
        pBook = realloc(pBook, i);
    };
    for (int j = 0; j < i; ++j){
        printf("%d \t%s \t%s \t%d \n",
               (pBook + j)->bookid, (pBook + j)->bookname,
               (pBook + j)->publisher, (pBook + j)->price);
    }
    free(pBook);
    // TODO: 엔터만 쳐도 스킵
    int temp;
    scanf("%d", &temp);
}

void add_books(MYSQL *conn) {
    printf("--- 도서 추가 ---\n");
    Book newbook;
    char query[255];
    // 정보 입력 scanf
    printf("도서 ID: ");
    scanf("%d", &newbook.bookid);
    printf("도서 명: ");
    scanf("%s", newbook.bookname);
    printf("출판사: ");
    scanf("%s", newbook.publisher);
    printf("가격: ");
    scanf("%d", &newbook.price);
    // query 문 작성 strcpy... "insert ....."
    sprintf(query, "insert into Book values (%d, '%s', '%s', %d)", newbook.bookid, newbook.bookname, newbook.publisher, newbook.price);
    // query 요청 mysql_query();
    if (mysql_query(conn, query))
    {
        printf("데이터 입력 실패: %s\n", mysql_error(conn));
    }
    else
    {
        printf("입력 성공\n");
    }

    return;
}


void delete_books(MYSQL *conn){
    //index번호 받기 scanf
    //지우는 쿼리

}
void update_books(MYSQL *conn){
    //모든번호 받기 scanf
    //변경하는 쿼리

}
void query_books(MYSQL *conn){
    //쿼리 스트링을 받아서
    //쿼리 요청
    //결과 프린트

}