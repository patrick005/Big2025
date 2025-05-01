#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h> // mkfifo
#include <sys/select.h>
#include <errno.h>

#define PIPE_PREFIX "/tmp/pipe"
#define NUM_PIPES 10
#define BUFFER_SIZE 128

void create_pipe(const char* path){
    unlink(path);
    if (mkfifo(path, 0666) == -1 && errno != EEXIST){
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }
}

typedef struct {
    char path[32];
    int fd;
}Pipe;

int open_pipe(const char* path){
    int fd = open(path, O_RDONLY | O_NONBLOCK);
    if (fd == -1){
        perror("open pipe");
        exit(EXIT_FAILURE);
    }
    return fd;
}

int main(void){
    Pipe pipes [NUM_PIPES]; // 파이프 정보를 담는 구조체 배열
    char buffer[BUFFER_SIZE]; // 데이터 버퍼
    for(int i = 0; i < NUM_PIPES; i++){ // 여러 개의 파이프 생성
        snprintf(pipes[i].path, sizeof(pipes[i].path), "%s%d", PIPE_PREFIX, i + 1);
        create_pipe(pipes[i].path);
    }

    printf("waiting client...\n"); // 클라이언트 연결 대기 메시지
    int max_fd = 0; // 감시할 최대 파일 디스크립터
    for(int i = 0; i < NUM_PIPES; i++){ // 모든 파이프 열기 및 최대 fd 찾기
        pipes[i].fd = open_pipe(pipes[i].path);
        if(pipes[i].fd > max_fd){
            max_fd = pipes[i].fd;
        }
    }
    max_fd++;

    // select setting
    fd_set read_fds; // 읽기 감지 fd 집합
    struct timeval timeout; // 타임아웃 설정
    int read_cnt; // 읽은 바이트 수

    printf("waiting for response from server\n"); // 서버 응답 대기 메시지 (오해 소지)

    while(1){
        FD_ZERO(&read_fds); // fd 집합 초기화
        for(int i = 0; i < NUM_PIPES; i++){ // 모든 파이프의 fd를 집합에 추가
            FD_SET(pipes[i].fd, &read_fds);
        }

        timeout.tv_sec = 15;
        timeout.tv_usec = 0; // 0ms

        int result = select(max_fd, &read_fds, 0, 0, &timeout); // select 호출
        if(result == -1){ // 에러
            puts("select() error");
            break;
        }else if(result == 0){ // 타임아웃
            puts("timeout");
        }else{ // 읽을 데이터 있는 fd 발견
            for(int i = 0; i < NUM_PIPES; i++){ // 모든 파이프 확인
                if(FD_ISSET(pipes[i].fd, &read_fds)){ // 해당 파이프에 데이터 도착
                    read_cnt = read(pipes[i].fd, buffer, BUFFER_SIZE); // 읽기
                    buffer[read_cnt] = '\0';
                    if(read_cnt > 0){
                        printf("pipe%d에서 읽은 메세지: %s\n", i + 1, buffer);
                    }else if(read_cnt == -1 && errno != EAGAIN && errno != EWOULDBLOCK){
                        printf("read pipe%d ", i + 1);
                    }
                }
            }
        }
    }

    for(int i = 0; i < NUM_PIPES; i++){ // 모든 파이프 닫고 제거
        close(pipes[i].fd);
        unlink(pipes[i].path);
    }
    return 0;
}

/**
 **컴포넌트:** 다중 클라이언트 지원 명명된 파이프 서버 (select 사용)

 **목표:** 여러 개의 명명된 파이프를 생성하고 `select()` 함수를 사용하여 동시에 여러 클라이언트로부터의 데이터를 비동기적으로 읽어들여 처리합니다.

 **기능:**
 - `NUM_PIPES` (여기서는 10) 개의 명명된 파이프(`/tmp/pipe1`부터 `/tmp/pipe10`까지)를 생성합니다.
 - 생성된 모든 파이프를 읽기 전용 및 비블로킹 모드로 엽니다.
 - `select()` 함수를 사용하여 열린 모든 파이프에서 읽을 데이터가 준비되었는지 감시합니다. 타임아웃은 15초로 설정되어 있습니다.
 - `select()`가 반환되면, 각 파이프를 순회하며 `FD_ISSET()` 매크로를 사용하여 해당 파이프에 읽을 데이터가 있는지 확인합니다.
 - 읽을 데이터가 있는 파이프에서 `read()` 함수를 호출하여 데이터를 읽고, 어떤 파이프에서 데이터를 읽었는지 함께 출력합니다.
 - 타임아웃 발생 시 "timeout" 메시지를 출력하고, `select()` 에러 발생 시 "select() error" 메시지를 출력하며 서버를 종료합니다.
 - 서버를 종료하거나 에러 발생 시 열었던 모든 파이프를 닫고 파일 시스템에서 제거합니다.

 **동작 방식:**
 이 서버는 여러 클라이언트가 동시에 데이터를 보낼 수 있도록 여러 개의 파이프를 미리 생성하고 감시합니다. `select()` 함수를 사용하여 어떤 파이프에 데이터가 도착했는지 효율적으로 확인하고, 도착한 데이터가 있는 파이프에서만 `read()`를 호출하여 데이터를 읽습니다. 이는 `pipe_server_select.c`와 유사하지만, 고정된 두 개의 파이프 대신 반복문을 사용하여 여러 개의 파이프를 생성하고 관리함으로써 **다중 클라이언트의 접속 및 통신을 관리**할 수 있도록 확장되었습니다. 각 클라이언트는 `/tmp/pipe[N]` 형태의 자신만의 파이프를 통해 서버에 데이터를 보낼 수 있습니다.
 */

 /*

pipe_server_select.c 와 같으나 반복문을 통한 다중 클라이언트의 접속을 관리함

*/

