//news_sender.c
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define TTL 64
#define BUF_SIZE 30
void error_handling(char *message);

int main(int argc, char *argv[]){
    int sock; // 소켓 파일 디스크립터 선언
    char buf[BUF_SIZE]; // 데이터 전송 버퍼 선언
    int str_len, recv_len, recv_cnt; // 미사용 변수 선언

    struct sockaddr_in mul_addr, from_addr; // 멀티캐스트, 송신자 주소 구조체 선언
    socklen_t from_addr_size; // 송신자 주소 크기 변수 선언 (미사용)
    int time_live = TTL; // 멀티캐스트 TTL 값 설정
    FILE *fp; // 파일 포인터 선언

    if (argc != 3){ // 멀티캐스트 그룹 IP 주소와 포트 번호 인자 확인
        printf("사용법: %s <GroupIP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_DGRAM, 0); // UDP 소켓 생성
    if (sock == -1){ // 소켓 생성 실패 시
        error_handling("socker() 열기 실패!!");
    }

    memset(&mul_addr, 0, sizeof(mul_addr)); // 멀티캐스트 주소 구조체 초기화
    mul_addr.sin_family = AF_INET; // IPv4 주소 체계 설정
    mul_addr.sin_addr.s_addr = inet_addr(argv[1]); // 멀티캐스트 그룹 IP 주소 변환
    mul_addr.sin_port = htons(atoi(argv[2])); // 멀티캐스트 포트 번호 변환

    setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, (void *)&time_live, sizeof(time_live)); // 멀티캐스트 TTL 설정

    if ((fp = fopen("/home/aa/Big2025/network/tcp/file_server.txt", "r")) == NULL){ // 파일 열기 시도
        error_handling("fopen() error");
    }

    while (!feof(fp)){ // 파일 끝까지 데이터 전송 반복
        fgets(buf, BUF_SIZE, fp); // 파일에서 데이터 읽기
        sendto(sock, buf, strlen(buf), 0, (struct sockaddr *)&mul_addr, sizeof(mul_addr)); // 데이터 멀티캐스트 전송
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
 * **컴포넌트:** 뉴스 송신자 (멀티캐스트)
 *
 * **목표:** 지정된 파일의 뉴스 데이터를 특정 멀티캐스트 그룹 IP 주소와 포트 번호로 전송하는 프로그램임.
 *
 * **프로세스:**
 * 1. 명령행 인수로 멀티캐스트 그룹 IP 주소와 포트 번호를 받음.
 * 2. UDP 소켓을 생성하고, 멀티캐스트 데이터 전송을 위한 주소 정보를 설정함.
 * 3. `setsockopt()` 함수를 사용하여 멀티캐스트 패킷의 TTL(Time To Live) 값을 설정함. 이는 멀티캐스트 패킷의 네트워크 생존 범위를 제어함.
 * 4. 지정된 경로의 텍스트 파일을 읽기 모드로 열고, 파일의 끝까지 다음 단계를 반복함.
 * 5. `fgets()` 함수로 파일에서 한 줄의 데이터를 읽어 버퍼에 저장함.
 * 6. `sendto()` 함수를 사용하여 버퍼의 데이터를 지정된 멀티캐스트 그룹 주소와 포트 번호로 전송함.
 * 7. 각 데이터 전송 후 2초 동안 대기함.
 * 8. 파일 읽기가 완료되면 파일을 닫고 소켓을 닫아 프로그램 종료함.
 * 9. 파일 열기 또는 소켓 생성에 실패하면 에러 메시지를 출력하고 프로그램을 종료함.
 *
 * **기능:**
 * - 파일 읽기 및 멀티캐스트 전송: 텍스트 파일에서 뉴스 데이터를 읽어 지정된 멀티캐스트 그룹으로 전송함.
 * - TTL 설정: 멀티캐스트 패킷의 네트워크 전파 범위를 제한함.
 * - 주기적 전송: 뉴스 데이터를 일정한 간격(2초)으로 전송함.
 *
 * **개념:**
 * - **멀티캐스트(Multicast):** 네트워크 상에서 특정 그룹의 호스트들에게 데이터를 효율적으로 전송하는 방식임.
 * - **UDP(User Datagram Protocol):** 비연결성 데이터 전송 프로토콜로, 멀티캐스트 통신에 주로 사용됨.
 * - **소켓(Socket):** 네트워크 통신을 위한 인터페이스임.
 * - **TTL(Time To Live):** 네트워크 패킷의 생존 시간을 나타내는 값으로, 라우터를 거칠 때마다 감소하며 0이 되면 패킷은 폐기됨. 멀티캐스트 패킷의 전파 범위를 제어하는 데 사용됨.
 * - **IP_MULTICAST_TTL:** 멀티캐스트 패킷의 TTL 값을 설정하는 소켓 옵션임.
 */