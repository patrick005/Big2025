// #include <mysql.h>
// #include <stdio.h>
// #include <string.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <time.h>
// //cc -o bookSql bookSql.c -I/usr/include/mysql -L/usr/lib/mysql -lmysqlclient
// typedef struct{
//     char player[40];
//     int score;
//     int count;
// }Bowling;

// enum menu{
//     START,  //1인용 시작 
//     SELECT, //사람수 지정
//     RANKING, //기록된 플레이 내역 확인
//     EXIT    //게임 종료
// };

// void startgame(MYSQL *conn);    //게임 실행
// void selectPlayer(MYSQL *conn); //플레이어 수 지정
// void ranking(MYSQL *conn);      //게임 내역 확인
// void exit_game(MYSQL *conn);    //게임 종료
// void print_menu(void);  //실행 메뉴판

// //게임 실행에 대한 main 정리 완
// int main(void){
//     //MYSQL 서버 접속
//     MYSQL *conn;
//     char *host = "localhost";
//     char *user = "myuser";
//     char *pass = "0000";
//     char *db = "mydb";
//     int port = 3306;
    
//     conn = mysql_init(NULL);//db 연결 요청 준비
//     if(mysql_real_connect(conn, host, user, pass, db, port, NULL, 0)){
//         printf("MySQL 연결 성공\n");
//     }else{
//         printf("MySQL 연결 실패\n");
//         return 1;
//     }

//     //게임 메뉴 실행
//     int choice;
//     while (true){
//         print_menu();
//         scanf("%d", &choice);
//         while(getchar() != '\n');
//         switch (choice){
//             case START:
//                 startgame(conn);
//                 break;
//             case SELECT:
//                 selectPlayer(conn);//libmysqlclient.so libmysqlclient.a
//                 break;
//             case RANKING:
//                 ranking(conn);
//                 break;
//             case EXIT:
//                 exit_game(conn);
//                 break;
//             default:
//                 printf("잘못된 접근입니다.\n");
//                 break;
//         }
//     }
//     mysql_close(conn);
//     return 0;
// }

// //실행 메뉴판 - 완
// void print_menu(void){

//     system("clear");
//     printf("=== 볼링 게임 ===\n");
//     printf("0. 1인용 게임 시작\n");
//     printf("1. 플레이어 수 지정\n");
//     printf("2. 랭킹 확인\n");
//     printf("3. 게임 종료\n");
// }

// //게임 실행(1인용 기준)
// void startgame(MYSQL *conn){
//     printf("--- 도서 추가 ---\n");
//     Book newbook;
//     char query[255];
//     // 정보 입력 scanf
//     printf("도서 ID: ");
//     scanf("%d", &newbook.bookid);
//     printf("도서 명: ");
//     scanf("%s", newbook.bookname);
//     printf("출판사: ");
//     scanf("%s", newbook.publisher);
//     printf("가격: ");
//     scanf("%d", &newbook.price);
//     // query 문 작성 strcpy... "insert ....."
//     sprintf(query, "insert into Book values (%d, '%s', '%s', %d)", newbook.bookid, newbook.bookname, newbook.publisher, newbook.price);
//     // query 요청 mysql_query();
//     if (mysql_query(conn, query)){
//         printf("데이터 입력 실패: %s\n", mysql_error(conn));
//     }else{
//         printf("입력 성공\n");
//     }
//     printf("엔터 키를 누르세요...\n");
//     getchar();
//     return;
// }

// //플레이어 수 지정
// void selectPlayer(MYSQL *conn){
//     printf("------------ 도서 변경 ------------\n");
//     printf("변경을 원하는 도서에 대해 입력하시오.\n");
//     //모든번호 받기 scanf
//     Book newbook;
//     char query[255];
//     // 정보 입력 scanf
//     printf("변경할 도서 ID: ");
//     scanf("%d", &newbook.bookid);
//     printf("변경할 도서 명: ");
//     scanf("%s", newbook.bookname);
//     printf("변경할 출판사: ");
//     scanf("%s", newbook.publisher);
//     printf("변경할 가격: ");
//     scanf("%d", &newbook.price);
//     getchar(); 

//     //변경하는 쿼리
//     sprintf(query, "update Book set bookname = '%s', publicher = '%s', price = %d where bookid = %d",
//             newbook.bookname, newbook.publisher, newbook.price, newbook.bookid);
//     if(mysql_query(conn, query)){
//         printf("도서 정보 변경 실패: %s\n", mysql_error(conn));
//     } else {
//         printf("도서 정보 변경 성공!\n");
//     }
//     printf("엔터 키를 누르세요...");
//     getchar(); 
// }

// //게임 내역 확인
// void ranking(MYSQL *conn){
//     MYSQL_RES *res;
//     MYSQL_ROW row;
//     char query[255];
//     strcpy(query, "select * from Book");

//     // 쿼리 요청
//     if (mysql_query(conn, query)){
//         printf("쿼리 실패");
//         return;
//     }
//     res = mysql_store_result(conn);
//     if (!res){
//         printf("가져오기 실패\n");
//         return;
//     }
//     Book *pBook;
//     pBook = (Book *)malloc(sizeof(Book));
//     int i = 0;
//     // 데이터 베이스의 정보를 구조체에 저장 - ORM
//     while (row = mysql_fetch_row(res)){
//         (pBook + i)->bookid = atoi(row[0]);
//         strcpy((pBook + i)->bookname, row[1]);
//         strcpy((pBook + i)->publisher, row[2]);
//         (pBook + i)->price = atoi(row[3]);
//         ++i;
//         pBook = realloc(pBook, sizeof(Book)*(i+1));
//     };
//     for (int j = 0; j < i; ++j){
//         printf("%d \t%s \t%s \t%d \n",
//                (pBook + j)->bookid, (pBook + j)->bookname,
//                (pBook + j)->publisher, (pBook + j)->price);
//     }
//     free(pBook);
//     mysql_free_result(res);
//     // TODO: 엔터만 쳐도 스킵
//     int temp;
//     scanf("%d", &temp);
// }

// //게임 종료
// void exit_game(MYSQL *conn){
//     exit(0);
// }

// //날짜 관련 작성 요망
// int Gametime(){
//     time_t t = time(NULL);
//     struct tm tm = *localtime(&t);
//     printf("%d-%02d-%02d", 1900 + tm.tm_year, 1 + tm.tm_mon, tm.tm_mday);
//     return 0;
// }













