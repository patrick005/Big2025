//shm_test2.c
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
#define COUNT 1000000

int main(void){
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SHM_SIZE);
    int *shm = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    *shm = 0; // 초기화
    printf("초기 카운터 값 : %d\n", *shm);

    pid_t pid = fork();
    if (pid == 0){
        printf("자식");
        for (int i = 0; i < COUNT; i++){
            (*shm)++;
        }
        munmap(shm, SHM_SIZE);
        exit(0);
    }else /*(pid == 1)*/{
        printf("부모");
        for (int i = 0; i < COUNT; i++){
            (*shm)++;
        }
        wait(NULL);

        printf("최종 카운터 값: %d\n", *shm);
        printf("예상 최종값: %d\n", COUNT * 2);
        printf("손실 된 증가 값 : %d\n", (COUNT * 2) - *shm);

        munmap(shm, SHM_SIZE); // 메모리 해제
        close(shm_fd);
        shm_unlink(SHM_NAME); // 언링크

    }
    
    return 0;
}
