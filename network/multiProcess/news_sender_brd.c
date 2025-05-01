//news_sender_brd.c
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 30
void error_handling(char *message);

int main(int argc, char *argv[]){
    int sock; // 소켓 파일 디스크립터 선언
    char buf[BUF_SIZE]; // 데이터 전송 버퍼 선언
    struct sockaddr_in mul_addr; // 멀티캐스트 주소 구조체 선언
    int so_brd = 1; // 브로드캐스트 활성화 플래그 선언 및 초기화
    FILE *fp; // 파일 포인터 선언

    if (argc != 3) {// 브로드캐스트 IP 주소와 포트 번호 인자 확인
        printf("사용법: %s <BROAD IP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_DGRAM, 0); // UDP 소켓 생성
    if (sock == -1){ // 소켓 생성 실패 시
        error_handling("socker() 열기 실패!!");
    }

    memset(&mul_addr, 0, sizeof(mul_addr)); // 멀티캐스트 주소 구조체 초기화
    mul_addr.sin_family = AF_INET; // IPv4 주소 체계 설정
    mul_addr.sin_addr.s_addr = inet_addr(argv[1]); // 브로드캐스트 IP 주소 변환
    mul_addr.sin_port = htons(atoi(argv[2])); // 포트 번호 변환

    setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (void *)&so_brd, sizeof(so_brd)); // 브로드캐스트 옵션 활성화

    if ((fp = fopen("/home/aa/Big2025/network/tcp/file_server.txt", "r")) == NULL){ // 파일 열기 시도
        error_handling("fopen() error");
    }

    while (!feof(fp)) {// 파일 끝까지 데이터 전송 반복
        fgets(buf, BUF_SIZE, fp); // 파일에서 데이터 읽기
        sendto(sock, buf, strlen(buf), 0, (struct sockaddr *)&mul_addr, sizeof(mul_addr)); // 데이터 브로드캐스트 전송
        sleep(2); // 2초 대기
    }
    fclose(fp); // 파일 닫기
    close(sock); // 소켓 닫기
    return 0;
}

void error_handling(char *message){
    fputs(message, stderr); // 에러 메시지 표준 에러 출력
    fputc('\n', stderr);
    exit(1); // 프로그램 종료
}

/**
 * **컴포넌트:** 뉴스 송신자 (브로드캐스트)
 *
 * **목표:** 지정된 파일에서 뉴스 데이터를 읽어와 네트워크의 특정 브로드캐스트 주소와 포트 번호로 전송하는 프로그램임.
 *
 * **프로세스:**
 * 1. 명령행 인수로 브로드캐스트 IP 주소와 포트 번호를 받음.
 * 2. `socket()` 함수를 사용하여 UDP 소켓을 생성함.
 * 3. 브로드캐스트를 활성화하기 위해 `setsockopt()` 함수를 사용하여 `SO_BROADCAST` 옵션을 설정함.
 * 4. 지정된 경로의 텍스트 파일을 읽기 모드로 열고, 파일 포인터를 얻음.
 * 5. `feof()` 함수를 사용하여 파일의 끝에 도달할 때까지 다음 작업을 반복함.
 * 6. `fgets()` 함수를 사용하여 파일에서 한 줄씩 데이터를 읽어 `buf` 버퍼에 저장함.
 * 7. `sendto()` 함수를 사용하여 `buf`의 내용을 지정된 브로드캐스트 주소와 포트 번호로 전송함.
 * 8. 각 데이터 전송 후 `sleep(2)` 함수를 사용하여 2초 동안 대기함.
 * 9. 파일의 끝에 도달하면 `fclose()` 함수를 사용하여 파일을 닫음.
 * 10. `close()` 함수를 사용하여 소켓을 닫고 프로그램 종료함.
 * 11. 파일 열기 실패 또는 소켓 생성 실패 시 `error_handling()` 함수를 호출하여 에러 메시지를 출력하고 프로그램 종료함.
 *
 * **기능:**
 * - 파일 읽기: 지정된 텍스트 파일에서 뉴스 데이터를 읽어옴.
 * - 브로드캐스트 전송: 읽어온 뉴스 데이터를 네트워크의 모든 호스트에게 동시에 전송함.
 * - 주기적 전송: 각 뉴스 데이터 전송 사이에 2초의 지연 시간을 두어 네트워크 부하를 조절함.
 *
 * **개념:**
 * - **브로드캐스트(Broadcast):** 네트워크 상의 모든 호스트에게 데이터를 동시에 전송하는 방식임.
 * - **UDP(User Datagram Protocol):** 비연결 지향적인 통신 프로토콜로, 빠른 데이터 전송에 유리함.
 * - **소켓(Socket):** 네트워크 통신을 위한 인터페이스임.
 * - **SO_BROADCAST:** 소켓에서 브로드캐스트 기능을 활성화하는 소켓 옵션임.
 */