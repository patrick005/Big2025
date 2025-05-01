//news_reciever.c
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
    struct ip_mreq join_addr; // 멀티캐스트 그룹 가입 요청 구조체 선언

    if (argc != 3){ // 그룹 IP 주소와 포트 번호 인자 확인
        printf("사용법: %s <GroupIP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_DGRAM, 0); // UDP 소켓 생성
    if (sock == -1){ // 소켓 생성 실패 시
        error_handling("socker() 만들기 실패");
    }

    memset(&mul_addr, 0, sizeof(mul_addr)); // 멀티캐스트 주소 구조체 초기화
    mul_addr.sin_family = AF_INET; // IPv4 주소 체계 설정
    mul_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 모든 인터페이스 주소로 설정 (수신용)
    mul_addr.sin_port = htons(atoi(argv[2])); // 멀티캐스트 포트 번호 설정

    if (bind(sock, (struct sockaddr *)&mul_addr, sizeof(mul_addr)) == -1){ // 소켓에 주소 바인딩
        error_handling("bind 에러!!!");
    }

    join_addr.imr_multiaddr.s_addr = inet_addr(argv[1]); // 가입할 멀티캐스트 그룹 IP 주소 설정
    join_addr.imr_interface.s_addr = htonl(INADDR_ANY); // 모든 네트워크 인터페이스를 통해 멀티캐스트 수신

    setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *)&join_addr, sizeof(join_addr)); // 멀티캐스트 그룹 가입 요청

    while (1){ // 데이터 수신 대기
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
 * **컴포넌트:** 뉴스 수신자 (멀티캐스트 그룹 지정)
 *
 * **목표:** 특정 멀티캐스트 그룹 IP 주소와 포트 번호로 전송되는 뉴스 데이터를 수신하여 표준 출력에 표시하는 프로그램임.
 *
 * **프로세스:**
 * 1. 명령행 인수로 멀티캐스트 그룹 IP 주소와 포트 번호를 받음.
 * 2. UDP 소켓을 생성하고, 모든 네트워크 인터페이스와 지정된 포트 번호에 바인딩하여 멀티캐스트 데이터를 수신할 준비를 함.
 * 3. `ip_mreq` 구조체를 설정하여 특정 멀티캐스트 그룹 IP 주소를 지정하고, 모든 인터페이스를 통해 해당 그룹의 데이터를 수신하도록 요청함.
 * 4. `setsockopt()` 함수를 사용하여 소켓 옵션을 `IP_ADD_MEMBERSHIP`으로 설정하고, `ip_mreq` 구조체를 전달하여 멀티캐스트 그룹에 가입함.
 * 5. 무한 루프를 통해 `recvfrom()` 함수로 멀티캐스트 데이터를 수신하고, 수신된 데이터를 표준 출력에 표시함.
 * 6. 데이터 수신 중 오류가 발생하면 루프를 종료하고 소켓을 닫음.
 * 7. 프로그램 종료 시 소켓을 닫음.
 * 8. 에러 발생 시 에러 메시지를 출력하고 프로그램을 종료함.
 *
 * **기능:**
 * - 특정 멀티캐스트 그룹 가입: 지정된 멀티캐스트 IP 주소의 데이터 스트림을 수신하기 위해 그룹에 참여함.
 * - 뉴스 데이터 수신 및 출력: 가입한 멀티캐스트 그룹으로부터 전송되는 뉴스 데이터를 실시간으로 수신하여 화면에 보여줌.
 *
 * **개념:**
 * - **멀티캐스트(Multicast):** 특정 그룹의 네트워크 호스트들에게 데이터를 효율적으로 전송하는 방식임.
 * - **UDP(User Datagram Protocol):** 비연결성 데이터 전송 프로토콜로, 멀티캐스트 통신에 주로 사용됨.
 * - **소켓(Socket):** 네트워크 통신을 위한 추상화된 인터페이스임.
 * - **IP_ADD_MEMBERSHIP:** 소켓을 특정 멀티캐스트 그룹에 가입시키는 IP 프로토콜 옵션임.
 * - **ip_mreq 구조체:** 멀티캐스트 그룹 가입 요청 시 사용되는 구조체로, 그룹 IP 주소와 로컬 인터페이스 정보를 담고 있음.
 */