#include "booksql.h"

void print_menu(void){

    system("clear");
    printf("=== 도서 관리 시스템 ===\n");
    printf("0. 도서 조회\n");
    printf("1. 도서 추가\n");
    printf("2. 도서 삭제\n");
    printf("3. 도서 변경\n");
    printf("4. 쿼리 입력\n");
    printf("5. 프로그램 종료\n");
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
        printf("가져오기 실패\n");
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
        pBook = realloc(pBook, sizeof(Book)*(i+1));
    };
    for (int j = 0; j < i; ++j){
        printf("%d \t%s \t%s \t%d \n",
               (pBook + j)->bookid, (pBook + j)->bookname,
               (pBook + j)->publisher, (pBook + j)->price);
    }
    free(pBook);
    mysql_free_result(res);
    // TODO: 엔터만 쳐도 스킵
    int temp;
    scanf("%d", &temp);
}

void add_books(MYSQL *conn){
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
    if (mysql_query(conn, query)){
        printf("데이터 입력 실패: %s\n", mysql_error(conn));
    }else{
        printf("입력 성공\n");
    }
    printf("엔터 키를 누르세요...\n");
    getchar();
    return;
}

void delete_books(MYSQL *conn){
    printf("------------ 도서 제거 ------------\n");
    printf("제거를 원하는 도서 번호를 입력하시오: ");
    //index번호 받기 scanf
    int bookid;
    char query[255];
    scanf("%d", &bookid);
    
    //지우는 쿼리
    sprintf(query, "delete from Book where bookid = %d", bookid);
    if(mysql_query(conn, query)){
        printf("도서 삭제 실패: %s\n", mysql_error(conn));
    } else {
        my_ulonglong affected_row = mysql_affected_rows(conn);
        printf("%lu 개 도서 삭제 성공\n", affected_row);
    }
    printf("엔터 키를 누르세요...");
    getchar(); 

}

void update_books(MYSQL *conn){
    printf("------------ 도서 변경 ------------\n");
    printf("변경을 원하는 도서에 대해 입력하시오.\n");
    //모든번호 받기 scanf
    Book newbook;
    char query[255];
    // 정보 입력 scanf
    printf("변경할 도서 ID: ");
    scanf("%d", &newbook.bookid);
    printf("변경할 도서 명: ");
    scanf("%s", newbook.bookname);
    printf("변경할 출판사: ");
    scanf("%s", newbook.publisher);
    printf("변경할 가격: ");
    scanf("%d", &newbook.price);
    getchar(); 

    //변경하는 쿼리
    sprintf(query, "update Book set bookname = '%s', publicher = '%s', price = %d where bookid = %d",
            newbook.bookname, newbook.publisher, newbook.price, newbook.bookid);
    if(mysql_query(conn, query)){
        printf("도서 정보 변경 실패: %s\n", mysql_error(conn));
    } else {
        printf("도서 정보 변경 성공!\n");
    }
    printf("엔터 키를 누르세요...");
    getchar(); 
}

void query_books(MYSQL *conn){
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[255];
    printf("------------ 쿼리 입력 ------------\n");
    printf("쿼리를 입력하세요: ");
    getchar();
    
    //gets(query);    
    fgets(query, sizeof(query), stdin);
    query[strspn(query, "\n")] = 0;
    
    scanf("%s", query);
    // 쿼리 요청
    if (mysql_query(conn, query)){
        printf("쿼리 실패: %s\n", mysql_error(conn));
        getchar(); 
        return ;
    }

    res = mysql_store_result(conn);
    if (res) { // 쿼리 결과가 있는 경우
        int num_fields = mysql_num_fields(res);
        MYSQL_FIELD *fields = mysql_fetch_fields(res);

        // 컬럼 이름 출력
        for(int i = 0; i < num_fields; i++){
            printf("%s\t", fields[i].name);
        }
        printf("\n");

        while((row = mysql_fetch_row(res))){
            for(int i = 0; i < num_fields; i++){
                printf("%s\t", row[i] ? row[i] : "NULL");
            }
            printf("\n");
        }
        mysql_free_result(res); // 결과 해제
    }else{ 
        if(mysql_field_count(conn) == 0) {
            printf("쿼리 실행 완료. 영향을 받은 행 수: %llu\n", (unsigned long long)mysql_affected_rows(conn));
        }else{
            printf("쿼리 실행 완료. (결과 없음)\n");
        }
    }
    printf("엔터 키를 누르세요...");
    getchar();
}

void exit_books(MYSQL *conn){
    exit(0);
}