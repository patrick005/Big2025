//Uecho_client.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 1024

void error_handling(char *message);

int main(int argc, char *argv[]){
    int sock;
    char message[BUF_SIZE];
    int str_len, recv_len, recv_cnt;

    struct sockaddr_in serv_addr, from_addr;
    socklen_t form_addr_size;

    if (argc != 3){
        printf("사용법: %s <IP><PORT>\n", argv[0]);
        exit(1);
    }
    
    sock = socket(PF_INET, SOCK_DGRAM, 0); //sock_stream -> tcp setting | SOCK_DGRAM -> udp setting
    if(sock == -1){
        error_handling("udp socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr)); // 주소에 대한 초기화
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]); // inet_addr : 중간 중간 .점들을 바꿔주는 함수 // 숫자로 받기에 localhost는 받을 수 없는 형태임 -> 바꾸면 가능
    serv_addr.sin_port = htons(atoi(argv[2]));

    // connet 필요하지 않음

    // 연결된 상태의 코드
    while (1){
        fputs("메시지를 넣으세요(Q 나가기): ",stdout);
        fgets(message, BUF_SIZE, stdin);
        if(!strcmp(message, "Q\n") || !strcmp(message, "q\n")){
            break;
        }
        message[strlen(message) - 1] = '\0'; // null termination
        // 보내는 코드
        str_len = sendto(sock, message, strlen(message), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
        printf("서버로 보내는 메세지: %s\n", message); // debugging message
        // 받는 코드
        str_len = recvfrom(sock, message, strlen(message), 0, (struct sockaddr*)&from_addr, &form_addr_size);        // recvfrom은 blocking mode
        message[str_len] = '\0'; // null termination
        printf("서버의 IP: %s\t PORT: %d\n", inet_ntoa(from_addr.sin_addr), ntohs(from_addr.sin_port)); // IP와 PORT를 받아서 출력
        printf("서버에서 온 메세지: %s\n", message); // debugging message
    }
    close(sock);

    return 0;
}

void error_handling(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

//./Uecho_client 192.168.0.89 8890

/*


*/