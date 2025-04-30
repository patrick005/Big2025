//file_client.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 30

void error_handling(char *message);

int main(int argc, char *argv[]){
    int sock;
    int str_len, recv_len, recv_cnt;
    FILE *fp;
    char message[BUF_SIZE];

    struct sockaddr_in serv_addr;
    int read_cnt;

    if (argc != 3){
        printf("사용법: %s <IP><PORT>\n", argv[0]);
        exit(1);
    }

    fp = fopen("/home/aa/Big2025/network/tcp/receive.txt", "wb");
    
    sock = socket(PF_INET, SOCK_STREAM, 0); //sock_stream -> tcp setting | SOCK_DGRAM -> udp setting
    if(sock == -1){
        error_handling("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr)); // tcp setting
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        error_handling("connect() error");// listen 상태인 서버에 접속
    }else{
        puts("connected server");
    }

    // 연결된 상태의 코드
    while ((read_cnt = read(sock, message, BUF_SIZE)) != 0){ // read()가 0이 될 때까지
        fwrite((void*)message, 1, read_cnt, fp);
    }

    puts("Received file data\n");
    write(sock, "Thank you", 10);
    fclose(fp);
    close(sock);

    return 0;
}

void error_handling(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

//./file_client 127.0.0.1 8890