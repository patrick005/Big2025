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
    int serv_sock, clnt_sock;
    int str_len, state;
    char message[BUF_SIZE];
    pid_t pid;

    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_addr_size;

    if (argc != 2){
        printf("사용법: %s <PORT>\n", argv[0]);
        exit(1);
    }

    // signal setting code
    struct sigaction act;
    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, 0);
    
    serv_sock = socket(PF_INET, SOCK_STREAM, 0); // tcp setting
    if (serv_sock == -1){
        error_handling("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    int option = 1;
    setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1){
        error_handling("bind() error");
    }
    if(listen(serv_sock, 5)){
        error_handling("listen() error");
    } // 5개의 클라이언트 대기

    
    // 연결된 상태의 코드....
    while(1){
        clnt_addr_size = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
        // accept : waiting
        if (clnt_sock == -1){
            // error_handling("accept() error");
            continue;
        }else{
            printf("connected client: %s \n", inet_ntoa(clnt_addr.sin_addr));
        }
        // fork, child : 기능: echo -> read -> write
        pid = fork();
        if(pid == -1){
            close(clnt_sock);
            continue;
        }
        if(pid == 0){
            close(serv_sock);
            while((str_len = read(clnt_sock, message, BUF_SIZE)) != 0){
                message[str_len] = '\0'; 
                puts(message);
                write(clnt_sock, message, str_len);
            }
            close(clnt_sock);
            printf("client disconnected form %s \n", inet_ntoa(clnt_addr.sin_addr));
            return 0;
        }else{
            close(clnt_sock);
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
    pid_t id = waitpid(-1, &status, WNOHANG); // 자식 프로세스의 종료 상태를 수집
    if(WIFEXITED(status)){
        printf("프로세스 제거 id: %d \n", id);
        printf("자식이 보낸 번호: %d \n", WEXITSTATUS(status));
    }
}


//./echo_server 8890