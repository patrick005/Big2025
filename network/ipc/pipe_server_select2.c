//pipe_server_select.c
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
    Pipe pipes [NUM_PIPES];
    char buffer[BUFFER_SIZE];
    for(int i = 0; i < NUM_PIPES; i++){
        snprintf(pipes[i].path, sizeof(pipes[i].path), "%s%d", PIPE_PREFIX, i + 1);
        create_pipe(pipes[i].path);
    }

    printf("waiting client...\n");
    int max_fd;
    for(int i = 0; i < NUM_PIPES; i++){
        pipes[i].fd = open_pipe(pipes[i].path);
        if(pipes[i].fd > max_fd){
            max_fd = pipes[i].fd;
        }
    }
    max_fd++;
    
    // select setting
    fd_set read_fds;
    struct timeval timeout;
    int read_cnt;
    
    printf("waiting for response from server\n");

    while(1){
        FD_ZERO(&read_fds);
        for(int i = 0; i < NUM_PIPES; i++){
            FD_SET(pipes[i].fd, &read_fds); // fd_set에 추가
        }

        timeout.tv_sec = 15;
        timeout.tv_usec = 0; // 0ms
        
        int result = select(max_fd, &read_fds, 0, 0, &timeout); // select() 호출
        if(result == -1){ // 에러
            puts("select() error");
            break;
        }else if(result == 0){ // timeout
            puts("timeout");
        }else{ // stdin에 데이터가 들어옴
            for(int i = 0; i < NUM_PIPES; i++){
                if(FD_ISSET(pipes[i].fd, &read_fds)){ // stdin이 fd_set에 포함되어 있으면
                    read_cnt = read(pipes[i].fd, buffer, BUFFER_SIZE); // 대기
                    buffer[read_cnt] = '\0';
                    if(read_cnt>0){
                        printf("pipe%d에서 읽은 메세지: %s\n", i + 1, buffer);
                    }else if(read_cnt == -1 && errno != EAGAIN && errno != EWOULDBLOCK){
                        printf("read pipe%d ", i + 1);
                    }
                }
            }
        }
    }

    for(int i = 0; i < NUM_PIPES; i++){
        close(pipes[i].fd);
        unlink(pipes[i].path);
    }
    return 0;
}


/*
1. server 작동
 cat /tmp/pipe1
 echo 'data from cli' >> /tmp/pipe2


2. server 작동
 client 작동

반복문을 통한 다중 클라이언트의 접속을 관리함



*/

