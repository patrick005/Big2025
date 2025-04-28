//pipe.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

#define BUFFER_SIZE 256

int main(void){
    // 파이프는 단방향 통신
    int pipe1_fd[2]; // 부모 -> 자식
    int pipe2_fd[2]; // 자식 -> 부모
    pid_t pid;
    char buffer[BUFFER_SIZE];

    pipe(pipe1_fd);
    pipe(pipe2_fd);

    pid = fork();
    if(pid == 0){
        // 자식
        close(pipe1_fd[1]); // 부모-> 자식 파이프의 쓰기 끝 닫기
        close(pipe2_fd[0]); // 자식->부모 파이프의 읽기 끝 닫기
        read(pipe1_fd[0], buffer, BUFFER_SIZE); // 대기 : 
        printf("Child received: %s\n", buffer);

        char *response = "Hello from Child";
        write(pipe2_fd[1], response, strlen(response) + 1);

        close(pipe1_fd[0]); // 부모-> 자식 파이프의 쓰기 끝 닫기
        close(pipe2_fd[1]); // 자식->부모 파이프의 읽기 끝 닫기
        exit(EXIT_SUCCESS);
    }else{
        //부모 프로세스
        close(pipe1_fd[0]); // 부모-> 자식 파이프의 쓰기 끝 닫기
        close(pipe2_fd[1]); // 자식->부모 파이프의 읽기 끝 닫기

        char *message = "Hello from Parent";
        write(pipe1_fd[1], message, strlen(message) + 1); // 이걸 버퍼에 채움

        getchar(); // 엔터를 해야 넘어가게 break느낌으로 넣어둠

        read(pipe2_fd[0], buffer, BUFFER_SIZE); // 대기 : 버퍼가 비어있으면 채워지기 전까지 대기하는 기능 때문에 여기서 한번 멈춤
        printf("parent received: %s\n", buffer);

        close(pipe1_fd[1]); // 부모-> 자식 파이프의 쓰기 끝 닫기
        close(pipe2_fd[0]); // 자식->부모 파이프의 읽기 끝 닫기
        
        wait(NULL);
        printf("자식 프로세스 종료\n");
    }
    
    return 0;
}