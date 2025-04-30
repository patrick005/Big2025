//wait.c
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>

int main(void){
    pid_t pid = fork();
    int status;

    if(pid == 0){ // 자식1
        return 3;
    }else{  // 부모
    
        pid = fork();

        if(pid == 0){ // 자식2
            exit(7);  //child process2 terminate
        }else{
            printf("Child process ID: %d\n", pid);
            wait(&status); // block until child process1 is terminated
            if(WIFEXITED(status)){
                printf("Child process1 sent message %d\n", WEXITSTATUS(status));
            }
            wait(&status);
            if(WIFEXITED(status)){
                printf("Child process2 sent message %d\n", WEXITSTATUS(status));
            }
            sleep(30); 
        }
    }
    return 0;
}