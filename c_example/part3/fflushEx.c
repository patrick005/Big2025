//fflushEx.c
#include <stdio.h>
#include <unistd.h>

int main(void){
 
    printf("hello, world!\n");
    fflush(stdout);
    sleep(1); //second 단위
    printf("hello, world!\n");
    fflush(stdout);
    sleep(1);
    printf("hello, world!\n");
    fflush(stdout);
    sleep(1);

    return 0;
}