//sigaction.c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void timeoutCallback(int sig);

int main(){
    // signal(SIGALRM, timeoutCallback);   // SIGALRM 시그널을 받을 때 timeoutCallback 함수를 호출하도록 설정 -> 바로 다음 루프
    struct sigaction act;
    act.sa_handler = timeoutCallback;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGALRM, &act, 0);

    alarm(2);

    for (int i = 0; i < 10; i++){
        puts("wait...");
        sleep(100); 
    }
    return 0;
}

void timeoutCallback(int sig){
    if(sig == SIGALRM){
        puts("Time out!");
    }
    alarm(2);
}