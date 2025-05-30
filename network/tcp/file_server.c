//file_server.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 30

void error_handling(char *message);

int main(int argc, char *argv[]){
    int serv_sock;
    int clnt_sock;
    int str_len;
    char message[BUF_SIZE];
    int read_cnt;
    FILE *fp;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    if (argc != 2){
        printf("사용법: %s <PORT>\n", argv[0]);
        exit(1);
    }
    
    serv_sock = socket(PF_INET, SOCK_STREAM, 0); // tcp setting
    if (serv_sock == -1){                                                         // socket: 소켓 생성
        error_handling("socket() error");
    }

    fp = fopen("/home/aa/Big2025/network/tcp/file_server.txt", "rb");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    int option = 1;
    setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1){ // bind: 주소를 소켓에 연결
        error_handling("bind() error");
    }
    if(listen(serv_sock, 5)){                                                     // listen: 클라이언트의 연결을 대기
        error_handling("listen() error");
    } 

    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
    if (clnt_sock == -1){                                                         // accept: 클라이언트의 연결을 수락
        error_handling("accept() error");
    }else{
        printf("connected client: %s \n", inet_ntoa(clnt_addr.sin_addr));
    }

    // 연결된 상태의 코드....
    while(1){
        read_cnt = fread((void *)message, 1, BUF_SIZE, fp);
        printf("outdata cnt \n");
        if (read_cnt < BUF_SIZE){
            write(clnt_sock, message, read_cnt);
            break;
        }
        write(clnt_sock, message, BUF_SIZE);
    }

    // 세련된 종료
    // shutdown: 소켓을 종료하는 함수, SHUT_WR: 송신 종료, SHUT_RD: 수신 종료, SHUT_RDWR: 송수신 모두 종료
    shutdown(clnt_sock, SHUT_WR); // 클라이언트에게 더 이상 보낼 것이 없음을 알림
    // shutdown(clnt_sock, SHUT_RD); // recvQ흐름을 방해한다
    shutdown(serv_sock, SHUT_RD); // 서버의 recvQ는 클라이언트 패킷 전달에 영향을 미치지 않음
    read(clnt_sock, message, BUF_SIZE); // 클라이언트가 종료할 때까지 대기
    printf("Message from client: %s \n", message); // sendQ 종료, recvQ 살아있음
    fclose(fp);
    close(clnt_sock);
    close(serv_sock);
    return 0;
}

void error_handling(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
//./file_server 8890