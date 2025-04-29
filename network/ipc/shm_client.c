//shm_client.c
#include <sys/mman.h>   
#include <fcntl.h>      
#include <stdlib.h>     
#include <stdio.h>
#include <unistd.h>     
#include <string.h>


int main(void){
    int shm_fd = shm_open("/myshm", O_RDWR, 0666); 
    if(shm_fd == -1){    // 생성 확인용 코드
        perror("shm_open");
        exit(1);
    }
    
    ftruncate(shm_fd, 4096); 
    char *shm = mmap(0, 4096, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0); 
    if (shm == MAP_FAILED){
        perror("mmap");
        exit(1);
    }
    

    // strcpy(shm, "Hello shared memory FROM process 1!"); // 이게 아니라 출력
    printf("Client read: %s\n", shm);

    // char temp[10];
    // scanf("%s", temp); // 대기할 이유가 없으니 제거

    munmap(shm, 4096);
    // shm_unlink("/myshm"); -> 서버에서 언링크지 여기서 할 이유가 없음
    return 0;
}

// gcc -o shm_client shm_client.c