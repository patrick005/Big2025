//echo_selectsrv.c
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct{
    int sockfd;
    struct sockaddr_in addr;
} ClientInfo;

void error_handling(char *message);

#define BUF_SIZE 100
#define MAX_CLIENTS 20

int main(int argc, char *argv[]){
    int serv_sock, clnt_sock; // 서버, 클라이언트 소켓 파일 디스크립터 선언
    int str_len, fd_max, fd_num; // 문자열 길이, 최대 파일 디스크립터, 준비된 파일 디스크립터 수
    char buf[BUF_SIZE]; // 버퍼 선언
    fd_set reads, cpy_reads; // 파일 디스크립터 셋 선언

    struct sockaddr_in serv_addr, clnt_addr; // 서버, 클라이언트 주소 구조체 선언
    struct timeval timeout; // 타임아웃 구조체 선언
    socklen_t clnt_addr_size; // 클라이언트 주소 크기 변수 선언

    ClientInfo clients[MAX_CLIENTS] = {0}; // 클라이언트 정보 배열 초기화
    int client_count = 0; // 클라이언트 수 카운트 변수 선언
    if (argc != 2){ // 포트 번호 인자 확인
        printf("사용법: %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0); // TCP 소켓 생성
    if (serv_sock == -1){ // 소켓 생성 실패 시
        error_handling("socker() 만들기 실패");
    }

    memset(&serv_addr, 0, sizeof(serv_addr)); // 서버 주소 구조체 초기화
    serv_addr.sin_family = AF_INET; // IPv4 주소 체계 설정
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 모든 인터페이스에 바인딩
    serv_addr.sin_port = htons(atoi(argv[1])); // 포트 번호 설정

    int option = 1;
    setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)); // 주소 재사용 옵션 설정
    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1){ // 바인딩
        error_handling("바인드 에러!!!");
    }
    if (listen(serv_sock, 5) == -1){ // 연결 대기열 설정
        error_handling("리슨 에러");
    }

    FD_ZERO(&reads); // reads 파일 디스크립터 셋 초기화
    FD_SET(serv_sock, &reads); // 서버 소켓을 reads 셋에 추가
    fd_max = serv_sock; // 최대 파일 디스크립터 갱신

    while (1){ // 메인 루프
        cpy_reads = reads; // reads 셋 복사
        timeout.tv_sec = 5; // 타임아웃 설정
        timeout.tv_usec = 0;

        if ((fd_num = select(fd_max + 1, &cpy_reads, 0, 0, &timeout)) == -1){ // select 함수 호출
            break;
        }
        if (fd_num == 0){ // 타임아웃 발생 시
            continue;
        }

        for (int i = 0; i < fd_max + 1; i++){ // 파일 디스크립터 순회
            if (FD_ISSET(i, &cpy_reads)){ // 이벤트 발생한 파일 디스크립터 확인
                if (i == serv_sock) { // 새로운 클라이언트 연결 요청
                    clnt_addr_size = sizeof(clnt_addr);
                    clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size); // 연결 수락
                    if (clnt_sock == -1){
                        continue;
                    }else{
                        FD_SET(clnt_sock, &reads); // 클라이언트 소켓을 reads 셋에 추가
                        if (fd_max < clnt_sock){ // 최대 파일 디스크립터 갱신
                            fd_max = clnt_sock;
                        }
                        if (client_count < MAX_CLIENTS){ // 클라이언트 정보 저장
                            clients[client_count].sockfd = clnt_sock;
                            clients[client_count].addr = clnt_addr;
                            client_count++;
                        }
                        printf("%d 번째 클라이언트 IP : %s \n", client_count, inet_ntoa(clnt_addr.sin_addr));
                    }
                }else { // 기존 클라이언트의 데이터 수신
                    str_len = read(i, buf, BUF_SIZE); // 데이터 읽기
                    if (str_len == 0){ // 연결 종료
                        FD_CLR(i, &reads); // 파일 디스크립터 셋에서 제거
                        close(i); // 소켓 닫기
                        for (int j = 0; j < client_count; ++j){ // 클라이언트 정보 갱신
                            if (clients[j].sockfd == i){
                                printf("client 연결 종료... %s \n", inet_ntoa(clients[j].addr.sin_addr));
                                clients[j] = clients[client_count - 1];
                                client_count--;
                                break;
                            }
                        }
                    }else{ // 데이터 수신
                        buf[str_len] = '\0'; // 널 문자 추가
                        for (int j = 0; j < client_count; ++j){ // 모든 클라이언트에게 데이터 전송 (에코)
                            if (clients[j].sockfd == i){
                                printf("%s : ", inet_ntoa(clients[j].addr.sin_addr));
                                puts(buf);
                                write(i, buf, str_len);
                            }
                        }
                    }
                }
            }
        }
    }

    close(serv_sock); // 서버 소켓 닫기

    return 0;
}

void error_handling(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

// ./echo_selectsrv 1234

/**
 * **컴포넌트:** 에코 서버 (select 사용)
 *
 * **목표:** 여러 클라이언트로부터 동시에 메시지를 수신하고, 받은 메시지를 모든 클라이언트에게 다시 전송(에코)하는 서버 프로그램임.
 *
 * **프로세스:**
 * 1. `socket()` 함수를 사용하여 TCP 서버 소켓을 생성함.
 * 2. 서버 주소 구조체(`sockaddr_in`)를 설정하고, `bind()` 함수로 소켓에 주소를 할당함.
 * 3. `listen()` 함수를 호출하여 클라이언트 연결 요청을 대기함.
 * 4. `select()` 함수를 사용하여 연결된 클라이언트로부터의 데이터 수신을 감시함.
 * 5. 새로운 클라이언트 연결 요청이 들어오면 `accept()` 함수로 연결을 수락하고, 클라이언트 정보를 배열에 저장함.
 * 6. 기존 클라이언트로부터 데이터가 수신되면 `read()` 함수로 데이터를 읽고, 연결된 모든 클라이언트에게 `write()` 함수를 사용하여 데이터를 전송함 (에코).
 * 7. 클라이언트 연결이 종료되면 해당 클라이언트 정보를 배열에서 제거하고 소켓을 닫음.
 * 8. `select()` 함수는 지정된 시간 동안 이벤트 발생을 기다리며, 타임아웃 발생 시에도 처리를 진행함.
 * 9. 에러 발생 시 `error_handling()` 함수를 호출하여 에러 메시지를 출력하고 프로그램을 종료함.
 *
 * **기능:**
 * - 다중 클라이언트 처리: `select()` 함수를 사용하여 여러 클라이언트의 연결 및 데이터 송수신을 동시에 처리함.
 * - 에코 기능: 클라이언트로부터 받은 메시지를 연결된 모든 클라이언트에게 다시 전송함.
 * - 연결 관리: 클라이언트 연결 설정 및 종료를 처리하고, 클라이언트 정보를 유지함.
 * - 비동기 I/O: `select()` 함수를 사용하여 비동기적으로 I/O 작업을 처리하여 효율성을 높임.
 *
 * **개념:**
 * - **소켓(Socket):** 네트워크 통신을 위한 인터페이스임.
 * - **TCP/IP:** 연결 지향적 통신을 제공하는 인터넷 프로토콜 스택의 핵심 프로토콜임.
 * - **select() 함수:** 여러 파일 디스크립터의 I/O 상태 변화를 감지하는 함수임.
 * - **에코 서버(Echo Server):** 클라이언트로부터 받은 데이터를 그대로 다시 보내는 서버임.
 * - **다중 클라이언트 처리:** 하나의 서버가 여러 클라이언트의 요청을 동시에 처리하는 기술임.
 */


