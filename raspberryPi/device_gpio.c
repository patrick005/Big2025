// 
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

// gpio pin (물리핀이 아닌 gpio핀 설정임)
#define LED1 23
#define LED2 24
#define LED3 25
#define LED4 1

int main(){

    int fd = open("/sys/class/gpio/gpio23/direcion", 0_WRONLY); //디바이스에 접근하는 리눅스의 가장 기본적인 시스템콜 이다
    write(fd, "OUT", strlen(OUT));
    close(fd);
    return 0;
}