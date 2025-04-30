//select.c
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>

#define BUF_SIZE 30

int main(void){
    fd_set reads, temps;
    int result, str_len;
    char buf[BUF_SIZE];
    
    struct timeval timeout;
    
    FD_ZERO(&reads); // 초기화
    FD_SET(0, &reads); // stdin을 fd_set에 추가
    
    while(1){
        timeout.tv_sec = 5; // 5초
        timeout.tv_usec = 0; // 0ms
        temps = reads; // fd_set을 복사
        result = select(1, &temps, 0, 0, &timeout); // select() 호출
        if(result == -1){ // 에러
            puts("select() error");
            break;
        }else if(result == 0){ // timeout
            puts("timeout");
        }else{ // stdin에 데이터가 들어옴
            if(FD_ISSET(0, &temps)){ // stdin이 fd_set에 포함되어 있으면
                str_len = read(0, buf, BUF_SIZE);
                buf[str_len] = 0; // null termination
                printf("message from console: %s", buf);
            }
        }
    }

    return 0;
}