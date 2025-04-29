//bound_host1.c
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void error_handling(char *message);

#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
    int serv_sock;
    char msg1[] = "면도를 하다 칼날에";
    char msg2[] = "턱 끝을 베고 마네요";
    char msg3[] = "문득 거울에 그대 얼굴 스친 것 같아";
    char msg4[] = "상처 따위는 잊은 채 멍하니 굳어지네요";
    char msg5[] = "까칠한 수염 깎아 주던 그대 기억에";

    struct sockaddr_in serv_addr;
    socklen_t clnt_addr_size;

    if (argc != 3)
    {
        printf("사용법: %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_DGRAM, 0); // UDP 설정
    if (serv_sock == -1)
        error_handling("socker() 만들기 실패");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]); // localhost 는 입력 받을 수 없는 코드
    serv_addr.sin_port = htons(atoi(argv[2]));

    sendto(serv_sock, msg1, sizeof(msg1), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    sendto(serv_sock, msg2, sizeof(msg2), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    sendto(serv_sock, msg3, sizeof(msg3), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    sendto(serv_sock, msg4, sizeof(msg4), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    sendto(serv_sock, msg5, sizeof(msg5), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    printf("send done!!\n");

    close(serv_sock);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}