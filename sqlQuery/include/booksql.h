#include <mysql.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
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
    QUERY,
    EXIT
};

void fetch_books(MYSQL *conn);
void add_books(MYSQL *conn);
void delete_books(MYSQL *conn);
void update_books(MYSQL *conn);
void query_books(MYSQL *conn);
void exit_books(MYSQL *conn);
void print_menu(void);