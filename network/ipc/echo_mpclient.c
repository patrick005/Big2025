// echo_mpclient.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 1024

void error_handling(char *message);

int main(int argc, char *argv[]){
    int sock; // 소켓 파일 디스크립터
    int str_len, recv_len, recv_cnt; // 메시지/수신 길이, 수신 횟수
    struct sockaddr_in serv_addr; // 서버 주소 구조체

    if (argc != 3){ // 인자 확인
        printf("사용법: %s <IP><PORT>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0); // TCP 소켓 생성
    if(sock == -1){
        error_handling("socket() error"); // 소켓 에러 처리
    }

    memset(&serv_addr, 0, sizeof(serv_addr)); // 주소 초기화
    serv_addr.sin_family = AF_INET; // IPv4 설정
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]); // IP 변환
    serv_addr.sin_port = htons(atoi(argv[2])); // 포트 변환

    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){ // 서버 연결
        error_handling("connect() error"); // 연결 에러 처리
    }else{
        puts("connected server"); // 연결 성공 메시지
    }

    char message[BUF_SIZE]; // 메시지 버퍼
    while (1){ // 메시지 송수신 루프
        fputs("메시지를 넣으세요(Q 나가기): ",stdout);
        fgets(message, BUF_SIZE, stdin);
        if(!strcmp(message, "Q\n") || !strcmp(message, "q\n")){
            break; // 종료 조건
        }
        message[strlen(message) - 1] =  '\0'; // 개행 제거
        str_len = write(sock, message, strlen(message)); // 서버에 전송
        recv_len = 0;
        while(recv_len < str_len){ // 전체 메시지 수신 루프
            recv_len = read(sock, message, BUF_SIZE - 1);
            if(recv_len == -1){
                fputs("read() error", stderr);
                break;
            }
            recv_len += recv_cnt; // 오류: recv_cnt 미초기화
        }
        message[str_len] = '\0'; // 널 종료
        printf("서버에 보낸 메세지: %s\n", message); // 수신 메시지 출력 (디버깅)
    }
    close(sock); // 소켓 닫기
    return 0;
}

void error_handling(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

//./echo_client 192.168.0.89 8890
//./echo_client 127.0.0.1 8890

/**
 * **컴포넌트:** 에코 클라이언트
 *
 * **목표:** 사용자가 입력한 메시지를 지정된 IP 주소와 포트 번호의 에코 서버로 전송하고, 서버로부터 동일한 메시지를 다시 받아 출력합니다.
 *
 * **기능:**
 * - 명령행 인수를 통해 서버 주소 정보를 받습니다.
 * - TCP 소켓을 생성하여 서버에 연결을 시도합니다.
 * - 연결 성공 후, 사용자로부터 메시지를 반복적으로 입력받아 서버로 전송합니다.
 * - 서버로부터 전송한 메시지를 다시 수신하여 사용자에게 보여줍니다.
 * - 'Q' 또는 'q'를 입력하면 연결을 종료하고 프로그램을 종료합니다.
 *
 * **동작 방식:**
 * 클라이언트는 소켓을 생성하고 서버에 연결합니다. 연결 후에는 사용자 입력 루프를 통해 메시지를 읽고 서버에 씁니다. 서버로부터 응답을 읽어와 사용자에게 출력합니다. 종료 조건이 충족되면 소켓을 닫고 종료합니다.
 */