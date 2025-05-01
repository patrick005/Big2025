//pipe_server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h> // mkfifo

#define BUFFER_SIZE 256
#define PIPE1 "/tmp/pipe1" // 서버 -> 클라이언트 파이프
#define PIPE2 "/tmp/pipe2" // 클라이언트 -> 서버 파이프

int main(void){
    int fd1, fd2; // 파일 디스크립터
    char buffer[BUFFER_SIZE]; // 데이터 버퍼

    mkfifo(PIPE1, 0666); // 명명된 파이프 생성 (서버 -> 클라이언트)
    mkfifo(PIPE2, 0666); // 명명된 파이프 생성 (클라이언트 -> 서버)

    printf("waiting client...\n"); // 클라이언트 대기 메시지

    fd1 = open(PIPE1, O_WRONLY); // 쓰기 전용 파이프 열기 (서버 -> 클라이언트)
    if (fd1 == -1){
        perror("open pipe1"); // 에러 처리
        exit(EXIT_FAILURE);
    }
    char *message = "Hello from Parent"; // 보낼 메시지
    write(fd1, message, strlen(message) + 1); // 파이프에 데이터 쓰기
    printf("서버에서 보낸 메세지: %s\n", message); // 보낸 메시지 출력
    close(fd1); // 파이프 닫기

    fd2 = open(PIPE2, O_RDONLY); // 읽기 전용 파이프 열기 (클라이언트 -> 서버)
    if (fd2 == -1){
        perror("open pipe2"); // 에러 처리
        exit(EXIT_FAILURE);
    }
    read(fd2, buffer, BUFFER_SIZE); // 파이프에서 데이터 읽기 (블로킹)
    printf("서버에서 읽은 메세지: %s\n", buffer); // 받은 메시지 출력
    close(fd2); // 파이프 닫기

    unlink(PIPE1); // 파이프 제거
    unlink(PIPE2); // 파이프 제거

    return 0;
}

/**
  **컴포넌트:** 명명된 파이프 서버

  **목표:** 두 개의 명명된 파이프를 생성하여 클라이언트에게 메시지를 보내고 클라이언트로부터 메시지를 받습니다.

  **기능:**
  - `/tmp/pipe1` (서버 -> 클라이언트)과 `/tmp/pipe2` (클라이언트 -> 서버) 이름으로 명명된 파이프를 생성합니다. `mkfifo` 함수는 FIFO (First-In, First-Out) 특성을 가진 특수 파일을 만듭니다.
  - `/tmp/pipe1`을 쓰기 전용 모드로 엽니다. `open` 함수는 클라이언트가 이 파이프를 읽기 위해 열 때까지 블로킹될 수 있습니다.
  - "Hello from Parent"라는 메시지를 `/tmp/pipe1` 파이프에 씁니다.
  - 쓴 메시지를 화면에 출력합니다.
  - `/tmp/pipe1` 파이프를 닫습니다.
  - `/tmp/pipe2`를 읽기 전용 모드로 엽니다. `open` 함수는 클라이언트가 이 파이프에 데이터를 쓸 때까지 블로킹됩니다.
  - `/tmp/pipe2` 파이프에서 데이터를 읽어와 화면에 출력합니다.
  - `/tmp/pipe2` 파이프를 닫습니다.
  - 프로그램 종료 시 생성했던 `/tmp/pipe1`과 `/tmp/pipe2` 파이프를 파일 시스템에서 제거합니다.

  **동작 방식:**
  서버는 먼저 `mkfifo` 함수를 사용하여 클라이언트와 통신할 두 개의 명명된 파이프를 생성합니다. 그 후, 서버는 `/tmp/pipe1`을 쓰기 위해 열고 클라이언트에게 메시지를 보냅니다. 메시지를 보낸 후 파이프를 닫고, 클라이언트로부터 메시지를 받기 위해 `/tmp/pipe2`를 읽기 위해 엽니다. `read` 함수는 클라이언트가 데이터를 쓸 때까지 서버를 멈추게 합니다. 데이터를 받으면 화면에 출력하고 파이프를 닫습니다. 마지막으로, 서버는 `unlink` 함수를 호출하여 생성했던 명명된 파이프들을 파일 시스템에서 제거합니다.
 */

/*
1. server 작동
 cat /tmp/pipe1
 echo "메세지" >> /tmp/pipe2

*/