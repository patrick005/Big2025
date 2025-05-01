//pipe_server_select.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h> // mkfifo
#include <sys/select.h>
#include <errno.h>

#define PIPE1 "/tmp/pipe1" // 서버 -> 클라이언트
#define PIPE2 "/tmp/pipe2" // 서버 -> 클라이언트
#define PIPE3 "/tmp/pipe3" // 서버 -> 클라이언트
#define PIPE4 "/tmp/pipe4" // 서버 -> 클라이언트
#define PIPE5 "/tmp/pipe5" // 서버 -> 클라이언트
#define BUF_SIZE 128


int main(void){
    int fd1, fd2, read_cnt;
    char buffer[BUF_SIZE];

    mkfifo(PIPE1, 0666); // making named pipe //first in first out
    mkfifo(PIPE2, 0666);


    printf("waiting client...\n");

    fd1 = open(PIPE1, O_RDONLY | O_NONBLOCK);
    if (fd1 == -1){
        perror("open pipe1");
        exit(EXIT_FAILURE);
    }
    fd2 = open(PIPE2, O_RDONLY | O_NONBLOCK); 
    if (fd2 == -1){
        perror("open pipe2");
        exit(EXIT_FAILURE);
    }


    // select setting
    fd_set read_fds;
    struct timeval timeout;
    int max_fd = fd1 +1;
    if(max_fd < fd1){
        max_fd = fd1;
    }
    if(max_fd < fd2){
        max_fd = fd2;
    }

    max_fd++;
    printf("waiting for response from server\n");

    while(1){
        FD_ZERO(&read_fds);
        FD_SET(fd1, &read_fds);
        FD_SET(fd2, &read_fds);

        timeout.tv_sec = 15;
        timeout.tv_usec = 0; // 0ms
        
        int result = select(max_fd, &read_fds, 0, 0, &timeout); // select() 호출
        if(result == -1){ // 에러
            puts("select() error");
            break;
        }else if(result == 0){ // timeout
            puts("timeout");
        }else{ // stdin에 데이터가 들어옴
            if(FD_ISSET(fd1, &read_fds)){ // stdin이 fd_set에 포함되어 있으면
                read_cnt = read(fd1, buffer, BUF_SIZE); // 대기
                buffer[read_cnt] = '\0';
                if(read_cnt>0){
                    printf("pipe1에서 읽은 메세지: %s\n", buffer);
                }else if(read_cnt == -1 && errno != EAGAIN && errno != EWOULDBLOCK){
                    perror("read pipe1");
                }
            }
            if(FD_ISSET(fd2, &read_fds)){ // stdin이 fd_set에 포함되어 있으면
                read_cnt = read(fd2, buffer, BUF_SIZE); // 대기
                buffer[read_cnt] = '\0';
                if(read_cnt>0){
                    printf("pipe2에서 읽은 메세지: %s\n", buffer);
                }else if(read_cnt == -1 && errno != EAGAIN && errno != EWOULDBLOCK){
                    perror("read pipe2");
                }
            }

        }
    }
    close(fd1);
    close(fd2);

    unlink(PIPE1);
    unlink(PIPE2);

    return 0;
}


/*
1. server 작동
 cat /tmp/pipe1
 echo 'data from cli' >> /tmp/pipe2


2. server 작동
 client 작동


*/

