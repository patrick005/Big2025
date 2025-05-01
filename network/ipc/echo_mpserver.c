//echo_mpserver.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>

void error_handling(char *message);
void read_childproc(int sig);

#define BUF_SIZE 30

void error_handling(char *message);

int main(int argc, char *argv[]){
    int serv_sock, clnt_sock; // 서버/클라이언트 소켓
    int str_len, state; // 메시지 길이, 상태
    char message[BUF_SIZE]; // 메시지 버퍼
    pid_t pid; // 프로세스 ID

    struct sockaddr_in serv_addr, clnt_addr; // 서버/클라이언트 주소
    socklen_t clnt_addr_size; // 클라이언트 주소 크기

    if (argc != 2){ // 포트 번호 인자 확인
        printf("사용법: %s <PORT>\n", argv[0]);
        exit(1);
    }

    // signal setting code
    struct sigaction act; // 시그널 액션 구조체
    act.sa_handler = read_childproc; // 핸들러 함수 지정
    sigemptyset(&act.sa_mask); // 시그널 마스크 초기화
    act.sa_flags = 0; // 플래그 초기화
    sigaction(SIGCHLD, &act, 0); // SIGCHLD 시그널 처리 설정

    serv_sock = socket(PF_INET, SOCK_STREAM, 0); // TCP 소켓 생성
    if (serv_sock == -1){
        error_handling("socket() error"); // 소켓 에러 처리
    }

    memset(&serv_addr, 0, sizeof(serv_addr)); // 서버 주소 초기화
    serv_addr.sin_family = AF_INET; // IPv4 설정
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 모든 IP 주소 허용
    serv_addr.sin_port = htons(atoi(argv[1])); // 포트 번호 설정

    int option = 1;
    setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)); // 주소 재사용 옵션 설정
    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1){ // 소켓에 주소 할당
        error_handling("bind() error"); // 바인드 에러 처리
    }
    if(listen(serv_sock, 5)){ // 연결 대기열 설정
        error_handling("listen() error"); // 리슨 에러 처리
    }

    // 연결된 상태의 코드....
    while(1){ // 클라이언트 연결 처리 루프
        clnt_addr_size = sizeof(clnt_addr); // 클라이언트 주소 크기 설정
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size); // 클라이언트 연결 수락
        if (clnt_sock == -1){
            // error_handling("accept() error"); // accept() 에러 처리 (주석 처리됨)
            continue; // 연결 실패 시 루프 계속
        }else{
            printf("connected client: %s \n", inet_ntoa(clnt_addr.sin_addr)); // 연결 성공 메시지
        }
        // fork, child : 기능: echo -> read -> write
        pid = fork(); // 자식 프로세스 생성
        if(pid == -1){ // fork() 에러 처리
            close(clnt_sock); // 클라이언트 소켓 닫기
            continue; // 루프 계속
        }
        if(pid == 0){ // 자식 프로세스
            close(serv_sock); // 자식 프로세스는 서버 소켓 닫기
            while((str_len = read(clnt_sock, message, BUF_SIZE)) != 0){ // 클라이언트로부터 메시지 읽기
                message[str_len] = '\0';
                printf("%s: ", inet_ntoa(clnt_addr.sin_addr));
                puts(message);
                write(clnt_sock, message, str_len); // 클라이언트에게 메시지 에코
            }
            close(clnt_sock); // 클라이언트 소켓 닫기
            printf("client disconnected form %s \n", inet_ntoa(clnt_addr.sin_addr)); // 클라이언트 연결 종료 메시지
            return 0; // 자식 프로세스 종료
        }else{ // 부모 프로세스
            close(clnt_sock); // 부모 프로세스는 클라이언트 소켓 닫기
        }
    }
    return 0;
}

void error_handling(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
void read_childproc(int sig){
    int status;
    pid_t id = waitpid(-1, &status, WNOHANG); // 종료된 자식 프로세스 ID 가져오기 (비블록)
    if(WIFEXITED(status)){ // 자식 프로세스가 정상 종료되었는지 확인
        printf("프로세스 제거 id: %d \n", id);
        printf("자식이 보낸 번호: %d \n", WEXITSTATUS(status)); // 자식 프로세스의 종료 코드 출력
    }
}

//./echo_server 8890

/**
 * **컴포넌트:** 멀티 프로세스 에코 서버
 *
 * **목표:** 클라이언트로부터 메시지를 받아 동일한 메시지를 다시 클라이언트에게 전송하는 에코 서버를 구현합니다. 각 클라이언트 연결은 별도의 자식 프로세스에서 처리하여 여러 클라이언트에게 동시에 서비스를 제공합니다.
 *
 * **기능:**
 * - 명령행 인수를 통해 포트 번호를 받습니다.
 * - TCP 소켓을 생성하여 클라이언트 연결을 대기합니다.
 * - 클라이언트 연결 시 `fork()`로 자식 프로세스를 생성하여 통신을 처리합니다.
 * - 자식 프로세스는 클라이언트로부터 메시지를 읽고 다시 씁니다 (에코).
 * - 부모 프로세스는 새로운 연결을 계속해서 수락합니다.
 * - 종료된 자식 프로세스는 시그널 핸들러를 통해 정리됩니다.
 *
 * **동작 방식:**
 * 서버는 소켓을 열고 지정된 포트에서 연결을 수락하는 대기 상태로 들어갑니다. 새로운 클라이언트 연결이 감지되면, `accept()`는 새로운 소켓을 반환하고 `fork()`는 이 연결을 처리할 별도의 자식 프로세스를 만듭니다. 자식 프로세스는 클라이언트와 통신하며 에코 서비스를 제공하고, 부모 프로세스는 다른 연결 요청을 계속해서 처리합니다. `SIGCHLD` 시그널 핸들러는 종료된 자식 프로세스를 정리하여 좀비 프로세스가 남지 않도록 합니다.
 */