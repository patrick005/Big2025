#include <mysql.h>  // MySQL 라이브러리 헤더 파일 포함
#include <stdio.h>   // 표준 입출력 라이브러리 포함
#include <string.h>  // 문자열 관련 함수 사용을 위한 라이브러리 포함

// 도서 정보를 저장하는 구조체 정의
typedef struct {
    int bookid;          // 도서 ID (정수형)
    char bookname[40];   // 도서 이름 (최대 40자 문자열)
    char publisher[40];  // 출판사 이름 (최대 40자 문자열)
    int price;           // 가격 (정수형)
} Book;

// 함수 선언: 데이터베이스에서 도서 목록을 가져오는 함수
void fetch_books(MYSQL *conn);

// 함수 선언: 데이터베이스에 새로운 도서를 추가하는 함수
void add_books(MYSQL *conn);

int main(void) {
    MYSQL *conn;                 // MySQL 연결을 위한 포인터
    char *host = "localhost";   // MySQL 서버 주소 (로컬호스트)
    char *user = "myuser";      // MySQL 사용자명
    char *pass = "0000";        // MySQL 비밀번호
    char *db = "mydb";          // 사용할 데이터베이스 이름
    int port = 3306;             // MySQL 서버 포트 번호
    int choice;                  // 사용자 선택을 저장할 변수

    // MySQL 연결 객체 초기화
    conn = mysql_init(NULL);
    
    // MySQL 서버에 연결 시도
    if (mysql_real_connect(conn, host, user, pass, db, port, NULL, 0)) {
        printf("MySQL 연결 성공\n");
    } else {
        printf("MySQL 연결 실패\n");
        return 1; // 연결 실패 시 프로그램 종료
    }
    
    // 무한 반복하여 사용자 입력을 받아 처리
    while (1) {
        printf("1번: 도서 목록 조회, 2번: 도서 추가 (선택하세요)\n");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                fetch_books(conn);  // 도서 목록 조회 함수 호출
                break;
            case 2:
                add_books(conn);    // 도서 추가 함수 호출
                break;
            default:
                printf("올바른 선택이 아닙니다. 다시 입력하세요.\n");
        }
    }
    
    // MySQL 연결 종료
    mysql_close(conn);
    return 0;
}

// 데이터베이스에서 도서 목록을 조회하는 함수
void fetch_books(MYSQL *conn) {
    MYSQL_RES *res;   // 결과 데이터를 저장할 포인터
    MYSQL_ROW row;    // 한 행(row) 데이터를 저장할 변수 /--데이터에 대해 행을 배열로써 저장함, 타입을 안가리고 다 문자로 취급
    char query[255];  // SQL 쿼리 문자열 ------------------빈쿼리 크게 만들고

    // SQL 쿼리: Book 테이블에서 모든 데이터 가져오기
    strcpy(query, "SELECT * FROM Book");//----------------------빈쿼리에 대해 book에서 모든 컬럼 다가져옴

    // // MySQL 서버에 쿼리 요청
    // if (mysql_query(conn, query)) {
    //     printf("쿼리 실행 실패\n"); --------------------디버깅
    //     return;
    // }
    
    // // 쿼리 실행 결과를 저장
    // res = mysql_store_result(conn);
    // if (!res) {
    //     printf("데이터 가져오기 실패\n");
    //     return;
    // }
    
    // 최대 100개의 도서를 저장할 배열 (메모리 동적 할당이 더 좋음)
    Book book[100];//-----------------------------------------------빈 배열 100짜리를 만듬
    int i = 0;
    
    // 결과 데이터를 한 줄씩 가져와 구조체 배열에 저장
    while ((row = mysql_fetch_row(res))) { // =-----------------------------------------'res를 불러와서' row로 들어갔을때 조건
        book[i].bookid = atoi(row[0]);       // 문자열을 정수로 변환하여 저장---------------0에서 시작을해서 book의 bookid[0]와 같은거 갲
        strcpy(book[i].bookname, row[1]);    // 도서 이름 복사
        strcpy(book[i].publisher, row[2]);   // 출판사 이름 복사
        book[i].price = atoi(row[3]);        // 가격 변환하여 저장
        ++i;  // 인덱스 증가
    }
    
    // 저장된 도서 목록 출력
    printf("도서 목록:\n");
    for (int j = 0; j < i; ++j) {
        printf("%d \t%s \t%s \t%d\n", 
            book[j].bookid, book[j].bookname, book[j].publisher, book[j].price);  
    }
    
    // MySQL 결과 데이터 해제
    mysql_free_result(res);
}

// 데이터베이스에 새로운 도서를 추가하는 함수
void add_books(MYSQL *conn) {
    printf("----- 도서 추가 -----\n");
    printf("번호, 책이름, 출판사, 가격을 순서대로 입력하세요: \n");
    
    Book newbook;   // 새 도서 정보를 저장할 구조체
    char query[255]; // SQL 쿼리 저장 변수

    // 사용자 입력을 받아 구조체에 저장
    scanf("%d %s %s %d", &newbook.bookid, newbook.bookname, newbook.publisher, &newbook.price);
    
    // SQL INSERT 쿼리 작성
    sprintf(query, "INSERT INTO Book VALUES (%d, '%s', '%s', %d)", 
            newbook.bookid, newbook.bookname, newbook.publisher, newbook.price);
    
    // 쿼리 실행 요청
    if (mysql_query(conn, query)) {
        printf("도서 추가 실패\n");
        return;
    }
    printf("도서가 성공적으로 추가되었습니다.\n");
}
