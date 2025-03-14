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
    
//     //1프레임씩 10번의 게임 진행--------------->while로 바꾸기
//     int frame;
//     for(frame = 0; frame < 10; frame++){

//         //1프레임 진행
//         int try1 = 0;
//         int try2 = 0;
//         printf("공을 굴려주세요\n");
//         scanf("%d", try1);
//         if(try1 = 10){
//             printf("스트라이크~!");
//             //다음 프레임으로 넘김
//         }else if(try1 <= 0 && try1 < 10){
//             //try1이란 변수로 저장
//             //10-try1의 수에대해 try2를 입력 받는다/ try2는 10-try1을 넘을 수 없다
//             printf("핀이 &d 개 남았네요\n", 10- try1);
//             printf("공을 굴려주세요\n");
//             scanf("%d", try2);
//             if(try2 = (10 - try1)){
//                 printf("스페어~!");
//             }else if(try2 <= 0 && try2 < 10 - try1){
//                 //점수를 적음
//             }else{
//                 printf("유효하지 않은 값입니다. 다시하세요.");
//             }
//         }else{
//             printf("유효하지 않은 값입니다. 다시하세요.");
//         }
//     }
    
//     //위 프레임 10세트 진행중 스트라이크 try1 = 10 이 나온 경우 다음 프레임 try1의 점수를 보너스 가산
//     // 단, 연속 스트라이크의 경우 보너스 점수로 30점을 넘길 수 없음
//     //스페어 처리를 했을 경우 다음 프레임 try1의 점수를 보너스로 가산


//     return;
// }

// //플레이어 수 지정
// void selectPlayer(MYSQL *conn){

// }

// //게임 내역 확인 (sql 출력 세부사항 변경요망)
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

// //게임 종료 - 완
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













