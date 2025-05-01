//pipe_server_select.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h> // mkfifo
#include <sys/select.h>
#include <errno.h>

#define PIPE1 "/tmp/pipe1" // 서버 -> 클라이언트 파이프 (읽기 전용)
#define PIPE2 "/tmp/pipe2" // 서버 -> 클라이언트 파이프 (읽기 전용)
#define PIPE3 "/tmp/pipe3" // 사용 안 함
#define PIPE4 "/tmp/pipe4" // 사용 안 함
#define PIPE5 "/tmp/pipe5" // 사용 안 함
#define BUF_SIZE 128


int main(void){
    int fd1, fd2, read_cnt; // 파일 디스크립터, 읽은 바이트 수
    char buffer[BUF_SIZE]; // 데이터 버퍼

    mkfifo(PIPE1, 0666); // 명명된 파이프 생성 (서버 -> 클라이언트 1)
    mkfifo(PIPE2, 0666); // 명명된 파이프 생성 (서버 -> 클라이언트 2)

    printf("waiting client...\n"); // 클라이언트 대기 메시지

    fd1 = open(PIPE1, O_RDONLY | O_NONBLOCK); // 읽기 전용, 비블로킹 모드로 파이프 열기
    if (fd1 == -1){
        perror("open pipe1"); // 에러 처리
        exit(EXIT_FAILURE);
    }
    fd2 = open(PIPE2, O_RDONLY | O_NONBLOCK); // 읽기 전용, 비블로킹 모드로 파이프 열기
    if (fd2 == -1){
        perror("open pipe2"); // 에러 처리
        exit(EXIT_FAILURE);
    }

    // select 설정
    fd_set read_fds; // 읽기를 감지할 파일 디스크립터 집합
    struct timeval timeout; // select() 타임아웃 설정
    int max_fd = fd1 + 1; // 감시할 최대 파일 디스크립터 값 초기화
    if (max_fd < fd2) {
        max_fd = fd2 + 1; // 최대 파일 디스크립터 값 갱신
    }

    printf("waiting for response from server\n"); // 서버 응답 대기 메시지 (오해 소지)

    while(1){
        FD_ZERO(&read_fds); // 파일 디스크립터 집합 초기화
        FD_SET(fd1, &read_fds); // fd1을 읽기 감지 집합에 추가
        FD_SET(fd2, &read_fds); // fd2를 읽기 감지 집합에 추가

        timeout.tv_sec = 15; // 타임아웃 시간 (초)
        timeout.tv_usec = 0; // 타임아웃 시간 (마이크로초)

        int result = select(max_fd, &read_fds, 0, 0, &timeout); // select() 호출, 읽기 이벤트 감지
        if(result == -1){ // 에러 발생
            puts("select() error");
            break;
        }else if(result == 0){ // 타임아웃 발생
            puts("timeout");
        }else{ // 읽을 데이터가 있는 파일 디스크립터 존재
            if(FD_ISSET(fd1, &read_fds)){ // fd1에 읽을 데이터가 있는지 확인
                read_cnt = read(fd1, buffer, BUF_SIZE); // 파이프에서 데이터 읽기
                buffer[read_cnt] = '\0';
                if(read_cnt > 0){
                    printf("pipe1에서 읽은 메세지: %s\n", buffer);
                }else if(read_cnt == -1 && errno != EAGAIN && errno != EWOULDBLOCK){
                    perror("read pipe1");
                }
            }
            if(FD_ISSET(fd2, &read_fds)){ // fd2에 읽을 데이터가 있는지 확인
                read_cnt = read(fd2, buffer, BUF_SIZE); // 파이프에서 데이터 읽기
                buffer[read_cnt] = '\0';
                if(read_cnt > 0){
                    printf("pipe2에서 읽은 메세지: %s\n", buffer);
                }else if(read_cnt == -1 && errno != EAGAIN && errno != EWOULDBLOCK){
                    perror("read pipe2");
                }
            }
        }
    }
    close(fd1); // 파이프 닫기
    close(fd2); // 파이프 닫기

    unlink(PIPE1); // 파이프 제거
    unlink(PIPE2); // 파이프 제거

    return 0;
}

/**
 * **컴포넌트:** 비동기 명명된 파이프 서버 (select 사용)
 *
 * **목표:** 여러 명명된 파이프(`/tmp/pipe1`, `/tmp/pipe2`)로부터 동시에 데이터를 읽어들이는 서버를 구현합니다. `select()` 함수를 사용하여 어떤 파이프에서 읽을 데이터가 준비되었는지 비동기적으로 감지합니다.
 *
 * **기능:**
 * - `/tmp/pipe1`과 `/tmp/pipe2` 이름으로 명명된 파이프를 생성합니다.
 * - 두 파이프를 읽기 전용 및 비블로킹 모드로 엽니다. 비블로킹 모드는 `read()` 호출이 즉시 반환되도록 하며, 읽을 데이터가 없으면 에러를 발생시킵니다 (EAGAIN 또는 EWOULDBLOCK).
 * - `select()` 함수를 사용하여 지정된 시간(15초) 동안 읽을 준비가 된 파일 디스크립터가 있는지 감시합니다.
 * - `select()`가 성공하면, `FD_ISSET()` 매크로를 사용하여 각 파이프에서 읽을 데이터가 있는지 확인합니다.
 * - 읽을 데이터가 있는 파이프에서 `read()` 함수를 호출하여 데이터를 읽고 화면에 출력합니다.
 * - `select()`가 타임아웃되면 "timeout" 메시지를 출력합니다.
 * - `select()`에서 에러가 발생하면 "select() error" 메시지를 출력하고 루프를 종료합니다.
 * - 사용이 끝난 파이프들을 닫고, 프로그램 종료 시 파이프들을 제거합니다.
 *
 * **동작 방식:**
 * 서버는 `mkfifo()`를 사용하여 두 개의 명명된 파이프를 생성합니다. `open()` 함수를 사용하여 이 파이프들을 비블로킹 읽기 모드로 엽니다. 메인 루프에서는 `select()` 함수를 호출하여 지정된 시간 동안 어떤 파이프에서 데이터를 읽을 수 있는지 기다립니다. `select()`가 반환되면, `FD_ISSET()`을 통해 각 파이프에 읽을 데이터가 있는지 확인하고, 있다면 `read()` 함수를 사용하여 데이터를 읽어옵니다. 비블로킹 모드이기 때문에 `read()`가 즉시 반환될 수 있으며, 읽을 데이터가 없으면 특정 에러 코드를 반환합니다. 서버는 이 과정을 반복하여 여러 파이프에서 동시에 데이터를 처리할 수 있도록 합니다.
 */