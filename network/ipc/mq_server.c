//mq_server.c
#include <stdio.h>
#include <fcntl.h>
#include <mqueue.h>
#include <string.h>
#include <stdlib.h>

#define QUEUE_NAME "/myqueue"
#define MAX_MSG_SIZE 128
#define QUEUE_PERMS 0666

int main(void){
    struct mq_attr attr; // 메시지 큐 속성 구조체
    attr.mq_flags = 0; // 플래그 초기화
    attr.mq_maxmsg = 10; // 최대 메시지 수 설정
    attr.mq_msgsize = MAX_MSG_SIZE; // 최대 메시지 크기 설정
    attr.mq_curmsgs = 0; // 현재 메시지 수 초기화

    mqd_t mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, QUEUE_PERMS, &attr); // 메시지 큐 생성 및 읽기 전용 열기

    char buffer[MAX_MSG_SIZE + 1]; // 메시지 수신 버퍼
    ssize_t bytes_read; // 읽은 바이트 수

    for (int i = 0; i < 5; i++){ // 5번 메시지 수신 시도
        bytes_read = mq_receive(mq, buffer, MAX_MSG_SIZE + 1, NULL); // 메시지 큐에서 메시지 수신
        buffer[bytes_read] = '\0'; // 널 종료 문자 추가
        printf("서버에서 받은 메세지: %s\n", buffer); // 받은 메시지 출력
    }

    mq_close(mq); // 메시지 큐 닫기
    mq_unlink(QUEUE_NAME); // 메시지 큐 제거

    return 0;
}

/**
 * **컴포넌트:** 메시지 큐 서버
 *
 * **목표:** 특정 이름의 메시지 큐를 생성하고, 클라이언트로부터 전송된 메시지를 최대 5번 수신하여 출력한 후 메시지 큐를 닫고 제거합니다.
 *
 * **기능:**
 * - `/myqueue`라는 이름의 메시지 큐를 생성합니다. `O_CREAT` 플래그는 큐가 없으면 새로 생성하도록 지시하고, `O_RDONLY` 플래그는 읽기 전용으로 큐를 엽니다.
 * - 메시지 큐의 속성을 설정합니다. 최대 10개의 메시지를 저장할 수 있으며, 각 메시지의 최대 크기는 128바이트입니다.
 * - `mq_receive` 함수를 사용하여 메시지 큐에서 메시지를 수신합니다. 이 함수는 큐에 메시지가 도착할 때까지 블로킹됩니다.
 * - 수신된 메시지를 표준 출력으로 표시합니다.
 * - 5개의 메시지를 수신하거나 오류가 발생하면 루프를 종료합니다.
 * - `mq_close` 함수를 사용하여 메시지 큐를 닫고, `mq_unlink` 함수를 사용하여 메시지 큐를 시스템에서 제거합니다.
 *
 * **동작 방식:**
 * 서버는 `mq_open`을 호출하여 `/myqueue`라는 이름의 메시지 큐를 생성하거나 엽니다. 큐의 속성을 설정하여 최대 메시지 수와 크기를 정의합니다. `for` 루프를 통해 `mq_receive`를 반복 호출하여 클라이언트가 전송한 메시지를 기다립니다. 메시지가 도착하면 내용을 읽어와 화면에 출력합니다. 지정된 횟수만큼 메시지를 수신한 후, 서버는 `mq_close`로 큐를 닫고 `mq_unlink`로 큐를 제거하여 다음 실행 시 새로운 큐를 만들 수 있도록 합니다.
 */

/*
추가 자료
메세지큐의 위치: /dev/mqueue/myqueue
echo 'form cli' >> /dev/mqueue/myqueue 버퍼형식이 아니라 안뜰거임
cat myqueue하면 여기 쌓인 메세지 정보가 출력

for문을 돌려서 여러개의 정보를 수용하게 묶어두고 ctrl + c로 강제종료하면 /dev/mqueue/myqueue에 쌓이는 것을 cat으로 확인할 수 있음
여기서 다시 서버를 돌리면 쌓인거에 대한 일괄적인 처리가 시작이 됨
*/