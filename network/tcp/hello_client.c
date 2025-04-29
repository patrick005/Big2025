//hello_client.c
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

    if (argc != 3){
        printf("사용법: %s <IP><PORT>\n", argv[0]);
        exit(1);
    }
    
    serv_sock = socket(PF_INET, SOCK_STREAM, 0); //sock_stream -> tcp setting | SOCK_DGRAM -> udp setting

    memset(&serv_addr, 0, sizeof(serv_addr)); // 주소에 대한 초기화
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]); // inet_addr : 중간 중간 .점들을 바꿔주는 함수
    serv_addr.sin_port = htons(atoi(argv[2]));

    connect(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); // connect: listen 상태인 서버에 접속
    
    // 연결된 상태의 코드
    // char message[30];
    // // write(clnt_sock, message, sizeof(message));
    // read(serv_sock, message, sizeof(message) - 1);
    // message[30] = '\0';
    char message[] = "강사님집에갈까요";
    write(serv_sock, message, sizeof(message));
    printf("서버에 보낸 메세지: %s\n", message);

    
    close(serv_sock);

    return 0;
}

//./hello_client  127.0.0.1 8888

/* ss -s : 소켓 정보 출력
aa@aa-virtual-machine:~/Big2025/build/network$ ss -s
Total: 899
TCP:   10 (estab 3, closed 0, orphaned 0, timewait 0)

Transport Total     IP        IPv6
RAW       1         0         1        
UDP       6         4         2        
TCP       10        9         1        
INET      17        13        4        
FRAG      0         0         0        

ss - t: tcp 정보 출력
aa@aa-virtual-machine:~/Big2025/build/network$ ss -t
State  Recv-Q  Send-Q   Local Address:Port     Peer Address:Port  Process  
ESTAB  0       0         192.168.0.89:55834   13.107.253.49:https     


ss -tulpm : 전체 정보 출력


ss -tulpn : 


*/