//echo_server.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 1024

void error_handling(char *message);

int main(int argc, char *argv[]){
    int serv_sock;
    int clnt_sock;
    int str_len;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    if (argc != 2){
        printf("사용법: %s <PORT>\n", argv[0]);
        exit(1);
    }
    
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

    for(int i = 0; i < 5; ++i){
        clnt_addr_size = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
        if (clnt_sock == -1){
            error_handling("accept() error");
        }else{
            printf("connected client %d : %s \n", i + 1, inet_ntoa(clnt_addr.sin_addr));
        }
        // 연결된 상태의 코드....
        char message[BUF_SIZE];
        while(str_len = read(clnt_sock, message, sizeof(message) - 1)){ // 읽을 때는 버퍼사이즈 전체를 읽어야함 공백문자 남을 수도 있음 / 보낼 땐 사이즈를 줄여도 됨
            message[str_len] = '\0';
            printf("서버 받은 메세지: %s \n", message);
            write(clnt_sock, message, str_len);
        }
        close(clnt_sock);
    }

    close(serv_sock);
    return 0;
}

void error_handling(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
//./echo_server 8890