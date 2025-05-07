// //echo_epollsrv.c
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

typedef struct{
    int sockfd;
    struct sockaddr_in addr;
} ClientInfo;

void error_handling(char *message);

#define BUF_SIZE 100
#define EPOLL_SIZE 20

int main(int argc, char *argv[]){
    int serv_sock, clnt_sock; // 서버, 클라이언트 소켓 파일 디스크립터 선언
    int str_len; // 문자열 길이
    char buf[BUF_SIZE]; // 버퍼 선언
    fd_set reads, cpy_reads; // 파일 디스크립터 셋 선언

    struct sockaddr_in serv_addr, clnt_addr; // 서버, 클라이언트 주소 구조체 선언
    socklen_t clnt_addr_size; // 클라이언트 주소 크기 변수 선언

    struct epoll_event *ep_events, event;
    int epfd, event_cnt;

    ClientInfo clients[EPOLL_SIZE] = {0}; // 클라이언트 정보 배열 초기화
    
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

    // epoll setting
    epfd = epoll_create(EPOLL_SIZE); // getting fd
    ep_events = malloc(sizeof(struct epoll_event) * EPOLL_SIZE);
    event.data.fd = serv_sock;      // match socket to fd
    epoll_ctl(epfd, EPOLL_CTL_ADD, serv_sock, &event);

    while (1){ // 메인 루프
        event_cnt = epoll_wait(epfd, ep_events, EPOLL_SIZE, -1); // optiona(-1) : 무한 대기
        if (event_cnt == -1){ 
            puts("epoll_wait() error");
            break;
        }

        for (int i = 0; i < event_cnt + 1; i++){ 
            if (ep_events[i].data.fd == serv_sock){ // if epoll detect changing server socket -> tring connect from client
                clnt_addr_size = sizeof(clnt_addr);
                clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size); // 연결 수락

                // add new client on epoll 
                event.events = EPOLLIN;
                event.data.fd = clnt_sock;
                epoll_ctl(epfd, EPOLL_CTL_ADD, clnt_sock, &event);
                printf("%ld 번째 클라이언트 IP : %s \n", sizeof(ep_events) / sizeof(ep_events[0]) +1, inet_ntoa(clnt_addr.sin_addr)); // ! 사이즈 체크 다시 확인

            }else { // 기존 클라이언트의 데이터 수신
                str_len = read(ep_events[i].data.fd, buf, BUF_SIZE); // 데이터 읽기
                if (str_len == 0){ // 연결 종료
                    epoll_ctl(epfd, EPOLL_CTL_DEL, ep_events[i].data.fd, NULL);
                    close(ep_events[i].data.fd); // 소켓 닫기
                    printf("client 연결 종료...\n");
                }else{ // 데이터 수신
                    buf[str_len] = '\0'; // 널 문자 추가
                    puts(buf);
                    write(ep_events[i].data.fd, buf, str_len);
                }
            }
        }
    }
    free(ep_events);
    close(serv_sock); // 서버 소켓 닫기

    return 0;
}

void error_handling(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

