//pipe_client.c
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

    printf("start client!\n"); // 클라이언트 시작 메시지

    fd1 = open(PIPE1, O_RDONLY); // 읽기 전용 파이프 열기 (서버 -> 클라이언트)
    if (fd1 == -1){
        perror("open pipe1"); // 에러 처리
        exit(EXIT_FAILURE);
    }
    read(fd1, buffer, BUFFER_SIZE); // 파이프에서 데이터 읽기 (블로킹)
    printf("클라이언트에서 받은 메세지: %s\n", buffer); // 받은 메시지 출력
    close(fd1); // 파이프 닫기

    fd2 = open(PIPE2, O_WRONLY); // 쓰기 전용 파이프 열기 (클라이언트 -> 서버)
    if (fd2 == -1){
        perror("open pipe2"); // 에러 처리
        exit(EXIT_FAILURE);
    }
    char *message = "Hello from Parent"; // 보낼 메시지
    write(fd2, message, strlen(message) + 1); // 파이프에 데이터 쓰기
    printf("서버로 보낸 메세지: %s\n", message); // 보낸 메시지 출력
    close(fd2); // 파이프 닫기

    unlink(PIPE1); // 파이프 제거
    unlink(PIPE2); // 파이프 제거

    return 0;
}

/**
 * **컴포넌트:** 명명된 파이프 클라이언트
 *
 * **목표:** 미리 생성된 두 개의 명명된 파이프를 사용하여 서버로부터 메시지를 읽고, 서버로 메시지를 보냅니다.
 *
 * **기능:**
 * - `/tmp/pipe1` (서버 -> 클라이언트) 파이프를 읽기 전용 모드로 엽니다. 이 `open` 호출은 서버가 파이프에 데이터를 쓸 때까지 블로킹됩니다.
 * - 파이프에서 데이터를 읽어와 화면에 출력합니다.
 * - `/tmp/pipe2` (클라이언트 -> 서버) 파이프를 쓰기 전용 모드로 엽니다. 이 `open` 호출은 서버가 파이프를 읽기 위해 열 때까지 블로킹될 수 있습니다.
 * - "Hello from Parent"라는 메시지를 파이프에 씁니다.
 * - 보낸 메시지를 화면에 출력합니다.
 * - 사용이 끝난 파이프들을 닫습니다.
 * - 프로그램 종료 시 `/tmp/pipe1`과 `/tmp/pipe2` 파이프를 제거합니다.
 *
 * **동작 방식:**
 * 클라이언트는 먼저 서버가 데이터를 보내올 `/tmp/pipe1`을 읽기 위해 엽니다. `read` 함수는 서버가 데이터를 쓸 때까지 클라이언트를 멈추게 합니다. 데이터를 받으면 화면에 출력하고 파이프를 닫습니다. 다음으로, 클라이언트는 서버로 데이터를 보낼 `/tmp/pipe2`를 쓰기 위해 엽니다. `write` 함수를 사용하여 메시지를 파이프에 쓰고, 보낸 메시지를 확인 후 파이프를 닫습니다. 마지막으로, 클라이언트는 `unlink` 함수를 호출하여 생성되었던 명명된 파이프들을 파일 시스템에서 제거합니다.
 */