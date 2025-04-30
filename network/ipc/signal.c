//signal.c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeoutCallback(int sig);
void keycontrolCallback(int sig);

int main(){
    signal(SIGALRM, timeoutCallback);   // SIGALRM 시그널을 받을 때 timeoutCallback 함수를 호출하도록 설정 -> 바로 다음 루프
    signal(SIGINT, keycontrolCallback); // SIGINT 시그널을 받을 때 keycontrolCallback 함수를 호출하도록 설정 -> 바로 다음 루프
    alarm(2);                           // 2초 후 Alram 실행

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
void keycontrolCallback(int sig){
    if (sig == SIGINT){
        puts("Ctrl + C pressed!");
  }
}