//getHostByAddr.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>

void error_handling(char *message);

int main(int argc, char *argv[]){
    int i;
    struct hostent *host;
    struct sockaddr_in addr;

    if (argc != 2){
        printf("사용법: %s <IP>\n", argv[0]);
        exit(0);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_addr.s_addr = inet_addr(argv[1]);

    host = gethostbyaddr((char *)&addr.sin_addr, 4, AF_INET); // gethostbyaddr: IP 주소를 호스트 이름으로 변환
    if(!host){
        error_handling("gethostbyname() error");
    }
    
    printf("공식 이름: %s \n", host->h_name); // 공식 호스트 이름

    for(i = 0; host->h_aliases[i]; ++i){
        printf("Aliases %d: %s \n", i + 1, host->h_aliases[i]); // 호스트의 별칭
    }
    
    printf("주소 타입: %d\n", host->h_addrtype);    // 주소 타입
    
    for(i = 0; host->h_addr_list[i]; ++i){  // 주소 리스트
        printf("주소 %d: %s \n", i + 1, inet_ntoa(*(struct in_addr *)host->h_addr_list[i]));
    }

    return 0;
}


void error_handling(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}


/*
aa@aa-virtual-machine:~/Big2025/build/network/utile$ ./getHostByAddr 8.8.8.8
공식 이름: dns.google 
주소 타입: 2
주소 1: 8.8.8.8 
aa@aa-virtual-machine:~/Big2025/build/network/utile$ ./getHostByAddr 127.0.0.1
공식 이름: localhost 
주소 타입: 2
주소 1: 127.0.0.1 
aa@aa-virtual-machine:~/Big2025/build/network/utile$ ./getHostByAddr 0.0.0.0
gethostbyname() error
aa@aa-virtual-machine:~/Big2025/build/network/utile$ ./getHostByAddr 192.168.0.1
공식 이름: _gateway 
주소 타입: 2
주소 1: 192.168.0.1 
*/