//shm_test.c
#include <sys/mman.h>   // shm_open
#include <fcntl.h>      // O_creat, O_RDWR
#include <stdlib.h>     // perror, exit
#include <stdio.h>
#include <unistd.h>     // ftruncate (비활성 참조라 안 뜨긴한데 필요함)
#include <string.h>


int main(void){
    int shm_fd = shm_open("/myshm", O_CREAT | O_RDWR, 0666); // shared memory file discription
    // if(shm_fd == -1){    // 생성 확인용 코드
    //     perror("shm_open");
    //     exit(1);
    // }
    ftruncate(shm_fd, 4096); // size 지정 안하면 알아서 정해주지만 명시
    char *shm = mmap(0, 4096, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0); // 바이트 단위로 자료를 포인터로 자료를 넘김

    strcpy(shm, "Hello shared memory FROM process 1!");

    char temp[10];
    scanf("%s", temp); // 입력 전까지 대기상태인 것을 활용한 대기열

    munmap(shm, 4096);       //mmap에 대한 해제
    shm_unlink("/myshm");    // cli에서의 unlink /dev/shm/myshm를 코드로 구현한 것
    return 0;
}

// ls /dev/shm/  --> 가상파일임 / os가 통로로써 열어준것이지 직접 파일을 생성한 것이 아님
// 를 통해 생성된 공유메모리 파일디스크립션의 생성된 것을 확인 할 수 있음
// 냅두면 메모리 리킹이니 이것을 해제 해야함
// unlink /dev/shm/myshm --> 코드로 구현할 것임
// cat /dev/shm/myshm -> 스트링 카피로 넣어둿던 내용물 확인 가능