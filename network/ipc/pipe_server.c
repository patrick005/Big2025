//pipe_server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h> // mkfifo

#define BUFFER_SIZE 256
#define PIPE1 "/tmp/pipe1" // 서버 -> 클라이언트
#define PIPE2 "/tmp/pipe2" // 클라이언트 -> 서버

int main(void){
    int fd1, fd2;
    char buffer[BUFFER_SIZE];
    // pipe(pipe1_fd);
    // pipe(pipe2_fd);
    mkfifo(PIPE1, 0666); // making named pipe //first in first out
    mkfifo(PIPE2, 0666);

    printf("waiting client...\n");

    fd1 = open(PIPE1, O_WRONLY); // 쓰기 전용
    if (fd1 == -1){
        perror("open pipe1");
        exit(EXIT_FAILURE);
    }    
    char *message = "Hello from Parent";
    write(fd1, message, strlen(message) + 1);
    printf("서버에서 보낸 메세지: %s\n", message);
    close(fd1);


    fd2 = open(PIPE2, O_RDONLY); // 읽기 전용
    if (fd2 == -1){
        perror("open pipe2");
        exit(EXIT_FAILURE);
    }
    read(fd2, buffer, BUFFER_SIZE); // 대기
    printf("서버에서 읽은 메세지: %s\n", buffer);
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