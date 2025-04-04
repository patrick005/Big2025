// 사용자모드에서 gpio에 대한 피지컬 주소에 대해 권한이 안되는거같다
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

// pys pin
#define LED1 23
int main(){

    int fd = open("/sys/class/gpio/export", O_WRONLY); // 23번핀에 대한 권한 부여
    write(fd, "23", strlen("23"));
    close(fd);
    fd = open("/sys/class/gpio/gpio23/direcion", O_WRONLY); //디바이스에 접근하는 리눅스의 가장 기본적인 시스템콜 이다
    write(fd, "OUT", strlen("OUT"));
    close(fd);
    fd = open("/sys/class/gpio/gpio23/value", O_WRONLY);

    for(int i = 0; i< 5; i++){
        write(fd, "1", strlen("1"));
        sleep(1);
        write(fd, "0", strlen("0"));
        sleep(1);
    }
    close(fd);
    
    fd = open("/sys/class/gpio/unexport", O_WRONLY); // 23번핀에 대한 권한 회수
    write(fd, "23`", strlen("23"));
    close(fd);

    return 0;
}