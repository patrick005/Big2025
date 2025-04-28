//hello_server.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    if (argc != 2){
        printf("사용법: %s <PORT>\n", argv[0]);
        exit(1);
    }
    
    serv_sock = socket(PF_INET, SOCK_STREAM, 0); //sock_stream -> tcp setting | SOCK_DGRAM -> udp setting

    memset(&serv_addr, 0, sizeof(serv_addr)); // 주소에 대한 초기화
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // ip정보처럼 주소가 들어감 / 이건 뭐가 오든 소켓을 열어준다는 코드로 작성 htonl: 엔디안 구분해줌
    serv_addr.sin_port = htons(atoi(argv[1])); // htons: atoi로 배열을 인트로 바꿔서 해당 포트값 지정

    int option = 1;
    setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)); // SO_REUSEADDR로 옵션 활성화
    bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    while (1)
    {
        listen(serv_sock, 5); // 대기!!!
        clnt_addr_size = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
        // 연결된 상태의 코드....
        // char message[] = "Hello, TCP IP!!";
        // write(clnt_sock, message, sizeof(message));
        char message[30];
        read(clnt_sock, message, sizeof(message) - 1);
        message[30] = '\0';
        printf("서버 받은 메세지: %s \n", message);
        close(clnt_sock);
    }

    close(serv_sock);
    return 0;
}

//./hello_server 8888