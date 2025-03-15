//fileDescriptor.c
//파일을 생성하는 두번째 방법
//리소스가 제한된 상황에서 사용하는 방법
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){
    int fd;
    fd = open("test2.dat",O_WRONLY | O_CREAT| O_TRUNC, 0644);
    if (fd == 1){
        printf("can't open file\n");
    }
    write(fd, "이것은 파일로 저장되는 예시 테이터 입니다.", 61);//뒤에 숫자 적으면 적은만큼만 출력, 많으면 가비지나 널이 들어갈것임
    close(fd);
    return 0;
}