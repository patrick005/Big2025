//endian_conv.c
#include <stdio.h>
#include <arpa/inet.h>

int main(void){
    unsigned short host_port = 0x1234;
    unsigned short net_port;
    unsigned long host_addr = 0x12345678;
    unsigned long net_addr;

    net_port = htons(host_port); //from host to net by short
    net_addr = htons(host_addr);

    printf("호스트의 포트는 :   %#x \n", host_port);
    printf("네트워크의 포트는 : %#x \n", net_port);
    printf("호스트 주소는 :     %#lx \n", host_addr);
    printf("네트워크 주소는 :   %#lx \n", net_addr);
    // host: little endian / net: big endian -> host는 빅인지 리틀인지 확인해야함
    return 0;
}