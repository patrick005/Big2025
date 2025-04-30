//pip_server_select.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h> // mkfifo
#include <sys/select.h>

#define PIPE1 "/tmp/pipe1" // 서버 -> 클라이언트
#define PIPE2 "/tmp/pipe2" // 서버 -> 클라이언트
#define PIPE3 "/tmp/pipe3" // 서버 -> 클라이언트
#define PIPE4 "/tmp/pipe4" // 서버 -> 클라이언트
#define PIPE5 "/tmp/pipe5" // 서버 -> 클라이언트
#define BUF_SIZE 128


int main(void){
    int fd1, fd2, fd3, fd4, fd5;
    char buffer[BUF_SIZE];

    mkfifo(PIPE1, 0666); // making named pipe //first in first out
    mkfifo(PIPE2, 0666);
    mkfifo(PIPE3, 0666);
    mkfifo(PIPE4, 0666);
    mkfifo(PIPE5, 0666);

    printf("waiting client...\n");

    fd1 = open(PIPE1, O_WRONLY); // 쓰기 전용
    if (fd1 == -1){
        perror("open pipe1");
        exit(EXIT_FAILURE);
    }
    fd2 = open(PIPE2, O_WRONLY); // 쓰기 전용
    if (fd2 == -1){
        perror("open pipe2");
        exit(EXIT_FAILURE);
    }
    fd3 = open(PIPE3, O_WRONLY); // 쓰기 전용
    if (fd3 == -1){
        perror("open pipe3");
        exit(EXIT_FAILURE);
    }
    fd4 = open(PIPE4, O_WRONLY); // 쓰기 전용
    if (fd4 == -1){
        perror("open pipe4");
        exit(EXIT_FAILURE);
    }
    fd5 = open(PIPE5, O_WRONLY); // 쓰기 전용
    if (fd5 == -1){
        perror("open pipe5");
        exit(EXIT_FAILURE);
    }

    // select setting
    fd_set read_fds;
    struct timeval timeout;
    int max_fd = fd1 +1;
    printf("waiting for response from server\n");

    while(1){
        FD_ZERO(&read_fds);
        FD_SET(fd1, &read_fds);
        FD_SET(fd2, &read_fds);
        FD_SET(fd3, &read_fds);
        FD_SET(fd4, &read_fds);
        FD_SET(fd5, &read_fds);

        timeout.tv_sec = 5;
        timeout.tv_usec = 0; // 0ms
        
        int result = select(1, &read_fds, 0, 0, &timeout); // select() 호출
        if(result == -1){ // 에러
            puts("select() error");
            break;
        }else if(result == 0){ // timeout
            puts("timeout");
        }else{ // stdin에 데이터가 들어옴
            if(FD_ISSET(0, &read_fds)){ // stdin이 fd_set에 포함되어 있으면
                read(fd1, buffer, BUF_SIZE); // 대기
                printf("서버에서 읽은 메세지: %s\n", buffer);
            }
            if(FD_ISSET(0, &read_fds)){ // stdin이 fd_set에 포함되어 있으면
                read(fd2, buffer, BUF_SIZE); // 대기
                printf("서버에서 읽은 메세지: %s\n", buffer);
            }
            if(FD_ISSET(0, &read_fds)){ // stdin이 fd_set에 포함되어 있으면
                read(fd3, buffer, BUF_SIZE); // 대기
                printf("서버에서 읽은 메세지: %s\n", buffer);
            }
            if(FD_ISSET(0, &read_fds)){ // stdin이 fd_set에 포함되어 있으면
                read(fd4, buffer, BUF_SIZE); // 대기
                printf("서버에서 읽은 메세지: %s\n", buffer);
            }
            if(FD_ISSET(0, &read_fds)){ // stdin이 fd_set에 포함되어 있으면
                read(fd5, buffer, BUF_SIZE); // 대기
                printf("서버에서 읽은 메세지: %s\n", buffer);
            }
        }
    }
    
    close(fd2);

    unlink(PIPE1);
    
    return 0;
}


/*
1. server 작동
 cat /tmp/pipe1
 echo 'data from cli' >> /tmp/pipe2


2. server 작동
 client 작동


*/

