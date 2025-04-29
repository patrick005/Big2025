//Uecho_server.c
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
    int str_len;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    if (argc != 2){
        printf("사용법: %s <PORT>\n", argv[0]);
        exit(1);
    }
    
    serv_sock = socket(PF_INET, SOCK_DGRAM, 0); // udp setting
    if (serv_sock == -1){
        error_handling("udp socket() error");
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
    // udp는 listen이 필요없음

    while(1){
        clnt_addr_size = sizeof(clnt_addr);
        
        // 연결된 상태의 코드....
        clnt_addr_size = sizeof(clnt_addr);
        char message[BUF_SIZE];
        str_len = recvfrom(serv_sock, message, BUF_SIZE, 0, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
        message[str_len] = '\0';
        printf("서버의 IP: %s\t PORT: %d\n", inet_ntoa(clnt_addr.sin_addr), ntohs(clnt_addr.sin_port)); // IP와 PORT를 받아서 출력
        printf("들어온 메세지는 : %s \n", message);
        sendto(serv_sock, message, str_len, 0, (struct sockaddr*)&clnt_addr, clnt_addr_size);
    }

    close(serv_sock);
    return 0;
}

void error_handling(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
//./Uecho_server 8890