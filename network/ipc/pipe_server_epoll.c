//pipe_server_epoll.c
// 1. epoll 프로그램 실행
// 2. echo 'data from cli' >> /tmp/pipe2
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 256
#define NUM_PIPES 30
#define PIPE_PREFIX "/tmp/pipe"
#define BUF_SIZE 128
#define MAX_EVENT 10

typedef struct{
    char path[32];
    int fd;
} Pipe;

void create_pipe(const char *path){
    unlink(path);
    if (mkfifo(path, 0666) == -1 && errno != EEXIST){
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }
}

int open_pipe(const char *path){
    int fd = open(path, O_RDONLY | O_NONBLOCK);
    if (fd == -1){
        perror("open pipe1");
        exit(EXIT_FAILURE);
    }
    return fd;
}

void read_pipe(int fd, const char *path, char *buffer, size_t buf_size){
    ssize_t read_cnt = read(fd, buffer, buf_size - 1);
    if (read_cnt > 0){
        buffer[read_cnt] = '\0';
        printf("파이프%d 에서 읽은 메세지: %s", fd, buffer);
    }else if (read_cnt == -1 && errno != EAGAIN && errno != EWOULDBLOCK){
        perror("read pipe1");
    }
}

// void reopen_pipe(Pipe *pipe, int epfd)
// {
//     close(pipe->fd);
//     pipe->fd = open_pipe(pipe->path);
// }

int main(){
    Pipe pipes[NUM_PIPES]; // 파이프 정보를 담는 구조체 배열
    char buffer[BUFFER_SIZE]; // 데이터 버퍼
    int epfd; // epoll 파일 디스크립터
    struct epoll_event event, events[NUM_PIPES]; // epoll 이벤트 구조체

    epfd = epoll_create1(0); // epoll 인스턴스 생성
    if (epfd == -1){
        perror("eoll_create 에러1!!");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NUM_PIPES; ++i){ // 여러 개의 파이프 생성
        snprintf(pipes[i].path, sizeof(pipes[i].path), "%s%d", PIPE_PREFIX, i + 1);
        create_pipe(pipes[i].path);
    }

    for (int i = 0; i < NUM_PIPES; ++i){ // 모든 파이프 열고 epoll에 등록
        pipes[i].fd = open_pipe(pipes[i].path);
        event.events = EPOLLIN; // 읽기 이벤트 감지
        event.data.ptr = &pipes[i]; // 사용자 데이터 설정 (Pipe 구조체 포인터)
        if (epoll_ctl(epfd, EPOLL_CTL_ADD, pipes[i].fd, &event) == -1){ // epoll에 파일 디스크립터 추가
            perror("epoll 에러!!!");
            exit(EXIT_FAILURE);
        }
    }

    printf("메세지 수신 대기 \n"); // 메시지 수신 대기 메시지
    while (1){ // 이벤트 루프
        int nfds = epoll_wait(epfd, events, MAX_EVENT, 10000); // epoll 이벤트 대기 (최대 10초)
        if (nfds == -1){ // 에러 발생
            puts("epoll wait 에러!!");
            break;
        }else if (nfds == 0){ // 타임아웃 발생
            puts("Time out !!");
            break;
        }
        else{ // 이벤트 발생
            for (int i = 0; i < nfds; ++i){ // 발생한 이벤트 처리
                Pipe *pipe = (Pipe *)events[i].data.ptr; // 이벤트와 연결된 Pipe 구조체 가져오기
                if (events[i].events & EPOLLIN){ // 읽기 가능 이벤트 발생
                    read_pipe(pipe->fd, pipe->path, buffer, BUFFER_SIZE); // 파이프에서 데이터 읽기
                }
                if (events[i].events & EPOLLERR){ // 에러 이벤트 발생
                    fprintf(stderr, "%s에서 오류 \n", pipe->path);
                }
                // if (events[i].events & EPOLLHUP)
                // {
                //     fprintf(stderr, "%s에서 연결 종료 \n", pipe->path);
                //     reopen_pipe(pipe, epfd);
                // }
            }
        }
    }
    for (int i = 0; i < NUM_PIPES; ++i){ // 모든 파이프 닫고 제거
        close(pipes[i].fd);
        unlink(pipes[i].path);
    }

    return 0;
}

/**
 **컴포넌트:** 비동기 명명된 파이프 서버 (epoll 사용)

 **목표:** 여러 개의 명명된 파이프를 생성하고 `epoll` 메커니즘을 사용하여 동시에 여러 클라이언트로부터의 데이터를 효율적으로 비동기적으로 읽어들여 처리합니다. `select()` 대신 `epoll`을 사용하여 더 많은 수의 파일 디스크립터를 효율적으로 처리할 수 있습니다.

 **기능:**
 - `NUM_PIPES` (여기서는 30) 개의 명명된 파이프(`/tmp/pipe1`부터 `/tmp/pipe30`까지)를 생성합니다.
 - 생성된 모든 파이프를 읽기 전용 및 비블로킹 모드로 엽니다.
 - `epoll_create1()`을 사용하여 epoll 인스턴스를 생성합니다.
 - 각 파이프의 파일 디스크립터를 epoll 인스턴스에 등록하고, 읽기 이벤트(`EPOLLIN`) 발생 시 알림을 받도록 설정합니다. 각 이벤트와 파이프 구조체를 연결합니다.
 - `epoll_wait()` 함수를 호출하여 등록된 파일 디스크립터에서 이벤트가 발생할 때까지 대기합니다. 타임아웃은 10초로 설정되어 있습니다.
 - 이벤트가 발생하면, 발생한 이벤트의 종류를 확인합니다. `EPOLLIN` 이벤트는 파이프에서 읽을 데이터가 있음을 나타내며, `EPOLLERR` 이벤트는 파이프에서 오류가 발생했음을 나타냅니다.
 - 읽을 데이터가 있는 파이프에서 `read_pipe()` 함수를 호출하여 데이터를 읽고 화면에 출력합니다.
 - 타임아웃 발생 시 "Time out !!" 메시지를 출력하고, `epoll_wait()` 에러 발생 시 에러 메시지를 출력하며 루프를 종료합니다.
 - 서버를 종료하거나 에러 발생 시 열었던 모든 파이프를 닫고 파일 시스템에서 제거합니다.

 **동작 방식:**
 이 서버는 여러 클라이언트가 동시에 데이터를 보낼 수 있도록 여러 개의 파이프를 미리 생성하고 `epoll`을 사용하여 이 파이프들을 효율적으로 감시합니다. `epoll_wait()`는 등록된 파일 디스크립터에서 I/O 이벤트가 발생할 때까지 대기하며, 이벤트가 발생한 파일 디스크립터 목록을 반환합니다. 서버는 이 목록을 순회하며 읽기 가능한 파이프에서 데이터를 읽어 처리합니다. `epoll`은 `select()`에 비해 더 많은 수의 파일 디스크립터를 효율적으로 처리할 수 있으며, 이벤트가 발생한 파일 디스크립터만 반환하므로 불필요한 검사를 줄여줍니다.
 */

 // ! epoll은 Linux 커널의 기능이므로, 다른 운영체제(예: Windows, macOS)에서는 사용할 수 없음