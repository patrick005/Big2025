//inet_addr.c
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

void print_addr(unsigned long conv_addr);

int main(void){
    const char *addr1 = "127.212.124.78"; // 01111111.11010100.011111100.01001110 7f.d4.7c.4e
    const char *addr2 = "127.212.124.256"; // 256: over 255 -> error
    struct sockaddr_in addr_inet, addr_inet2;

    unsigned long conv_addr = inet_addr(addr1);
    print_addr(conv_addr); // 0x4e 7c d4 7f -> 엔디안이 아니라 단순히 숫자가 바뀐 것
    
    conv_addr = inet_addr(addr2);
    print_addr(conv_addr);

    int ret = inet_pton(AF_INET, addr1, &addr_inet.sin_addr); // return value: 1 when success
    if(ret){
        printf("네트워크 인티저 addr: %#x \n", addr_inet.sin_addr.s_addr); // 0x4e7cd47f 위와 같음
        // printf("sockaddr 의 s_data: %#x \n", ((struct sockaddr *)&addr_inet)->sa_data); // sa_data: 14 bytes / 0xa63270a2 / 4바이트만 출력됨, 기존의도와 달리 10바이트 증발 -> for문으로 해보면 될거임
    }

    char buffer[20];
    char *buffer_ptr;
    /*
    buffer_ptr = inet_ntoa(addr_inet.sin_addr);
    strcpy(buffer, buffer_ptr);
    printf("네트워크 형식(111.111.111.111)의 문자열: %s \n", buffer); // 숫자로 바뀐게 다시 문자열로 그대로 127.212.124.78 출력 */
    printf("네트워크 형식(111.111.111.111)의 문자열: %s \n", inet_ntoa(addr_inet.sin_addr)); // 위에 3줄을 한 줄로 표현

    
    addr_inet2.sin_addr.s_addr = htonl(0x10203040);
    buffer_ptr = inet_ntoa(addr_inet2.sin_addr);
    strcpy(buffer, buffer_ptr);
    printf("네트워크 형식(111.111.111.111)의 문자열: %s \n", buffer); // 0x10203040을 16진수를 10진수로써 16.32.48.64 출력
    return 0;
}

void print_addr(unsigned long conv_addr){
    if(conv_addr == INADDR_NONE){ //if fail to convert
        printf("Error occured! \n");
    }else{
        printf("네트워크의 인트 addr: %#lx \n", conv_addr);
    }

}