//wait.c
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>

int main(void){
    pid_t pid = fork();
    int status;

    if(pid == 0){ // 자식1
        sleep(15);
        return 3;
    }else{  // 부모
        printf("Child process ID: %d\n", pid);
        while(!waitpid(-1, &status, WNOHANG)){
            sleep(3);
            puts("sleep 3 sec\n");
        }
        if(WIFEXITED(status)){
            printf("Child process1 sent message %d\n", WEXITSTATUS(status));
        }
        sleep(30);
    }
    return 0;
}