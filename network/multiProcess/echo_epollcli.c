// echo_epollcli.c
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[]){
    int sock; // 소켓 파일 디스크립터 선언
    struct sockaddr_in serv_addr; // 서버 주소 구조체 선언

    if (argc != 3) { // 인자 개수 확인
        printf("사용법: %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0); // TCP 소켓 생성
    if (sock == -1){ // 소켓 생성 실패 시
        error_handling("socker() 열기 실패!!");
    }

    memset(&serv_addr, 0, sizeof(serv_addr)); // 서버 주소 구조체 초기화
    serv_addr.sin_family = AF_INET; // IPv4 주소 체계 설정
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]); // 서버 IP 주소 변환
    serv_addr.sin_port = htons(atoi(argv[2])); // 서버 포트 번호 변환

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1){ // 서버 연결 시도
        error_handling("connet() 연결 실패!!!");
    }else{ // 연결 성공 시
        puts("Connected............");
    }

    char message[BUF_SIZE]; // 메시지 버퍼 선언
    int str_len, recv_len, recv_cnt; // 메시지 길이 변수 선언

    while (1){ // 메시지 송수신 반복
        fputs("메세지를 넣으세요(Q 나가기): ", stdout);
        fgets(message, BUF_SIZE, stdin); // 사용자 입력 받기
        if (!strcmp(message, "q\n") || !strcmp(message, "Q\n")){ // 종료 조건 확인
            break;
        }
        message[strlen(message) - 1] = '\0'; // 개행 문자 제거
        write(sock, message, strlen(message)); // 서버에 메시지 전송

        str_len = read(sock, message, BUF_SIZE - 1); // 서버로부터 메시지 수신
        if (str_len == -1){ // 읽기 실패 시
            fputs("read() 에러!!!", stderr);
            break;
        }
        message[str_len] = '\0'; // 널 종료 문자 추가
        printf("서버에서 온 메세지: %s\n", message);
    }
    close(sock); // 소켓 닫기

    return 0;
}

void error_handling(char *message){
    fputs(message, stderr); // 에러 메시지 출력
    fputc('\n', stderr);
    exit(1); // 프로그램 종료
}

// ./echo_selectcli 127.0.0.1 1234

/**
 * **컴포넌트:** 에코 클라이언트
 *
 * **목표:** 사용자가 입력한 메시지를 지정된 IP 주소와 포트 번호의 에코 서버로 전송하고, 서버로부터 동일한 메시지를 다시 받아 출력하는 클라이언트 프로그램임.
 *
 * **프로세스:**
 * 1. 명령행 인수로 서버 IP 주소와 포트 번호를 받음.
 * 2. `socket()` 함수를 사용하여 TCP 소켓을 생성함.
 * 3. 서버 주소 구조체(`sockaddr_in`)를 설정하고, `connect()` 함수를 사용하여 서버에 연결을 시도함.
 * 4. 연결 성공 시 사용자로부터 메시지를 입력받는 무한 루프를 시작함.
 * 5. `fgets()` 함수로 사용자 입력을 읽고, "Q" 또는 "q"를 입력하면 루프를 종료함.
 * 6. `write()` 함수를 사용하여 입력된 메시지를 서버로 전송함.
 * 7. `read()` 함수를 사용하여 서버로부터 에코된 메시지를 수신함.
 * 8. 수신된 메시지를 화면에 출력함.
 * 9. 루프 종료 후 `close()` 함수를 사용하여 소켓을 닫고 프로그램 종료함.
 * 10. 에러 발생 시 `error_handling()` 함수를 호출하여 에러 메시지를 출력하고 프로그램 종료함.
 *
 * **기능:**
 * - 서버 연결: 지정된 IP와 포트로 서버에 TCP 연결을 시도함.
 * - 메시지 송신: 사용자로부터 입력받은 메시지를 서버로 전송함.
 * - 메시지 수신: 서버로부터 에코된 메시지를 수신하여 사용자에게 보여줌.
 * - 종료: 사용자가 "Q" 또는 "q"를 입력하면 안전하게 연결을 종료하고 프로그램을 종료함.
 *
 * **개념:**
 * - **소켓(Socket):** 네트워크 통신을 위한 인터페이스임.
 * - **TCP/IP:** 인터넷 프로토콜 스택의 핵심 프로토콜로, 연결 지향적 통신을 제공함.
 * - **클라이언트-서버 모델:** 클라이언트가 서버에 요청을 보내고 서버가 응답하는 통신 모델임.
 * - **에코(Echo):** 받은 데이터를 그대로 다시 보내는 동작임.
 */