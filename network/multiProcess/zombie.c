//zombie.c
#include <stdio.h>
#include <unistd.h>

// function

int main(void){
    pid_t pid = fork();

    if(pid == 0){ // 자식
        puts("hello, I'm child process");
    }else{  // 부모
        printf("Child Porcess ID: %d\n", pid);
        sleep(30);
    }
    // 부모 프로세스가 종료되면 자식 프로세스는 좀비 상태가 된다.
    if(pid == 0){
        puts("End of Child Process");
    }else{
        puts("End of Parent Process"); // 30초 후 종료
    }


    return 0;
}