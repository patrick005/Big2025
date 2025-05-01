//news_reciever_brd.c
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
    int str_len; // 수신한 문자열 길이 변수 선언
    char buf[BUF_SIZE]; // 수신 버퍼 선언

    struct sockaddr_in mul_addr; // 멀티캐스트 주소 구조체 선언

    if (argc != 2){ // 포트 번호 인자 확인
        printf("사용법: %s <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_DGRAM, 0); // UDP 소켓 생성
    if (sock == -1){ // 소켓 생성 실패 시
        error_handling("socker() 만들기 실패");
    }

    memset(&mul_addr, 0, sizeof(mul_addr)); // 멀티캐스트 주소 구조체 초기화
    mul_addr.sin_family = AF_INET; // IPv4 주소 체계 설정
    mul_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 모든 인터페이스 주소로 설정
    mul_addr.sin_port = htons(atoi(argv[1])); // 멀티캐스트 포트 번호 설정

    if (bind(sock, (struct sockaddr *)&mul_addr, sizeof(mul_addr)) == -1){ // 소켓에 주소 바인딩
        error_handling("bind 에러!!!");
    }

    setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *)&mul_addr, sizeof(mul_addr)); // 멀티캐스트 그룹 가입

    while (1){ // 데이터 수신 무한 루프
        str_len = recvfrom(sock, buf, BUF_SIZE - 1, 0, NULL, 0); // 데이터 수신
        if (str_len < 0){ // 수신 에러 발생 시
            break;
        }
        buf[str_len] = 0; // 널 종료 문자 추가
        fputs(buf, stdout); // 수신된 데이터 표준 출력
    }
    close(sock); // 소켓 닫기

    return 0;
}

void error_handling(char *message){
    fputs(message, stderr); // 에러 메시지 표준 에러 출력
    fputc('\n', stderr);
    exit(1); // 프로그램 종료
}

/**
 * **컴포넌트:** 뉴스 수신자 (멀티캐스트)
 *
 * **목표:** 특정 멀티캐스트 그룹으로 전송되는 뉴스 데이터를 수신하여 표준 출력에 표시하는 프로그램임.
 *
 * **프로세스:**
 * 1. 명령행 인수로 멀티캐스트 포트 번호를 받음.
 * 2. `socket()` 함수를 사용하여 UDP 소켓을 생성함.
 * 3. 멀티캐스트 주소 구조체(`sockaddr_in`)를 설정하고, 모든 인터페이스 주소와 지정된 포트 번호로 바인딩함.
 * 4. `setsockopt()` 함수를 사용하여 해당 소켓을 특정 멀티캐스트 그룹에 가입시킴. 이를 통해 해당 그룹으로 전송되는 패킷을 수신할 수 있게 됨.
 * 5. 무한 루프를 통해 `recvfrom()` 함수를 사용하여 멀티캐스트 데이터를 수신함. 송신자 정보는 필요 없으므로 NULL, 0으로 설정함.
 * 6. 수신된 데이터의 길이를 확인하고, 에러가 발생하면 루프를 종료함.
 * 7. 수신된 데이터를 널 종료하고 `fputs()` 함수를 사용하여 표준 출력에 표시함.
 * 8. 루프 종료 후 `close()` 함수를 사용하여 소켓을 닫고 프로그램 종료함.
 * 9. 에러 발생 시 `error_handling()` 함수를 호출하여 에러 메시지를 출력하고 프로그램 종료함.
 *
 * **기능:**
 * - 멀티캐스트 그룹 가입: 특정 멀티캐스트 주소와 포트 번호로 전송되는 데이터를 수신하기 위해 그룹에 참여함.
 * - 뉴스 데이터 수신: 가입된 멀티캐스트 그룹으로부터 전송되는 뉴스 데이터를 실시간으로 수신함.
 * - 데이터 출력: 수신된 뉴스 데이터를 표준 출력에 표시하여 사용자에게 제공함.
 *
 * **개념:**
 * - **멀티캐스트(Multicast):** 네트워크 상에서 특정 그룹의 호스트들에게 데이터를 동시에 전송하는 방식임.
 * - **UDP(User Datagram Protocol):** 비연결 지향적인 통신 프로토콜로, 빠른 데이터 전송에 유리함.
 * - **소켓(Socket):** 네트워크 통신을 위한 인터페이스임.
 * - **IP_ADD_MEMBERSHIP:** 소켓을 특정 멀티캐스트 그룹에 가입시키는 소켓 옵션임.
 */