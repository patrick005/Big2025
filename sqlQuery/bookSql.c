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

void fetch_books(MYSQL *conn);
void add_books(MYSQL *conn);

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
        printf("1번, 2번 고르세요\n");
        scanf("%d", &choice);
        switch (choice){
        case 1:
            fetch_books(conn);
            break;
        case 2:
            add_books(conn);//libmysqlclient.so libmysqlclient.a
        }
    }
    mysql_close(conn);
    // printf("----- 도서 추가 -----\n");
    // printf("번호, 책이름, 상호, 가격을 순서대로 적어주세요.\n");
    // Book newbook;
    // char query[255];
    // // 정보 입력 
    // scanf("%d %s %s %d", query);
    // //query문 작성 strcpy..."insert ..."
    // INTSERT INTO book VALUES newbook;
    // sprintf(query, "insert into Book Values (%d, %s, %s, %d)", newbook.bookid, newbook.bookname,newbook.price,newbook.publisher);
    // //query 요청 mysql_query();
    return 0;
}
//cc -o bookSql bookSql.c -I/usr/include/mysql -L/usr/lib/mysql -lmysqlclient

void fetch_books(MYSQL *conn){
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[255];
    strcpy(query, "select * from Book");

    //쿼리요청
    if(mysql_query(conn, query)){
        printf("쿼리 실패"); 
        return ;
        }
    res = mysql_store_result(conn);
    if (!res){
        printf("가져오기 실패\n");
        return ;
    }
    
    Book book[100]; // 동적할당이 좋지만 일단 스택에 만들어보기
    int i = 0;  //동적할당 스택에 구현
    // 데이터 베이스의 정보를 구조체에 저장 -> ORM
    while (row = mysql_fetch_row(res)){
        book[i].bookid = atoi(row[0]);      //동적할당 스택에 구현
        strcpy(book[i].bookname, row[1]);
        strcpy(book[i].publisher, row[2]);
        book[i].price = atoi(row[3]);
        ++i;
        // printf("%s\t", row[0]);
        // printf("%s\t", row[1]);
        // printf("%s\t", row[2]);
        // printf("%d\t\n", atoi(row[3]));
    };
    for(int j = 0; j < i; ++j){
        printf("%d \t%s \t%s \t%d\n", 
            book[j].bookid, book[j].bookname, book[j].publisher, book[j].price);  
    }
}

void add_books(MYSQL *conn) {
    printf("----- 도서 추가 -----\n");
    printf("번호, 책이름, 출판사, 가격을 순서대로 입력하세요: \n");
    
    Book newbook;   // 새 도서 정보를 저장할 구조체
    char query[255]; // 쿼리 저장 변수
    scanf("%d %s %s %d", &newbook.bookid, newbook.bookname, newbook.publisher, &newbook.price);
    // scanf("%d %s %s %d", query);
    sprintf(query, "INSERT INTO Book VALUES (%d, '%s', '%s', %d)", 
            newbook.bookid, newbook.bookname, newbook.publisher, newbook.price);
    
    if (mysql_query(conn, query)) {
        printf("도서 추가 실패\n");
    }else{
        printf("도서 추가 성공\n");
    }
    
    printf("도서가 성공적으로 추가되었습니다.\n");
}

