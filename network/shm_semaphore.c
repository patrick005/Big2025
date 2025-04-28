//shm_semaphore.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <string.h>
#include <wait.h>

#define SHM_NAME "/myshm"
#define SEM_NAME "/mysem"
#define SHM_SIZE 128

int main(void){
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SHM_SIZE);
    char *shm = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 1); // 동시 접근 제한

    pid_t pid = fork();
    if (pid == 0){
        sem_wait(sem); // 접근 권한 요청 코드 // 다른 프로세서가 사용중이면 대기
        printf("자식");
        printf("Child read: %s\n", shm);
        sem_post(sem); // 다쓰고 해제한다는 코드 // 세마포어 해제

        wait(NULL); // fork 된 다른 프로세서 종료 대기.

        munmap(shm, SHM_SIZE);
        sem_close(sem);
        exit(0);
    }else /*(pid == 1)*/{
        sem_wait(sem);
        printf("부모");
        strcpy(shm, "Hello from Parent");
        printf("Parent wrote: %s\n", shm);
        sem_post(sem);

        munmap(shm, SHM_SIZE);
        sem_close(sem);
        exit(0);

    }
    getchar();

    munmap(shm, SHM_SIZE); // 메모리 해제
    close(shm_fd);
    shm_unlink(SHM_NAME); // 언링크
    // 메모리 매핑이기에 위에꺼 먼저하고 세마포어를 닫는다
    sem_close(sem); // 세마포어 해제
    sem_unlink(SEM_NAME);

    return 0;
}


/*
aa@aa-virtual-machine:~/Big2025$ ps -al
F S   UID     PID    PPID  C PRI  NI ADDR SZ WCHAN  TTY          TIME CMD
0 S  1000    1243    1235  0  80   0 - 56135 do_pol tty2     00:00:00 gnome-session-b
0 S  1000    6570    6474  0  80   0 -   695 wait_w pts/4    00:00:00 shm_semaphore
1 S  1000    6571    6570  0  80   0 -   695 n_tty_ pts/4    00:00:00 shm_semaphore
4 R  1000    6659    6615  0  80   0 -  3516 -      pts/5    00:00:00 ps

따로 돌기에 스레드처럼 쓸 수 있지만 그럴바엔 스레드를 쓰는것이 나을 것이다.
*/