//mq_client.c
#include <stdio.h>
#include <fcntl.h>
#include <mqueue.h>
#include <string.h>
#include <stdlib.h>

#define QUEUE_NAME "/myqueue"
#define MAX_MSG_SIZE 128

int main(void){

    mqd_t mq = mq_open(QUEUE_NAME, O_WRONLY); // 쓰기 전용 메시지 큐 열기

    char buffer[] = "Hello form Client!"; // 보낼 메시지
    mq_send(mq, buffer, strlen(buffer) + 1, 0); // 메시지 큐에 메시지 전송
    printf("서버로 보낸 메세지: %s\n", buffer); // 보낸 메시지 출력

    mq_close(mq); // 메시지 큐 닫기

    return 0;
}


/**
 * **컴포넌트:** 메시지 큐 클라이언트
 *
 * **목표:** 미리 정의된 이름의 메시지 큐에 간단한 메시지를 전송합니다.
 *
 * **기능:**
 * - 특정 이름(`/myqueue`)의 메시지 큐를 쓰기 전용 모드로 엽니다.
 * - "Hello form Client!"라는 메시지를 담은 버퍼를 생성합니다.
 * - `mq_send` 함수를 사용하여 메시지 큐에 버퍼의 내용을 전송합니다. 메시지 우선순위는 0으로 설정됩니다.
 * - 전송된 메시지를 표준 출력으로 확인합니다.
 * - 사용이 끝난 메시지 큐를 닫습니다.
 *
 * **동작 방식:**
 * 클라이언트는 `mq_open`을 통해 서버가 생성했을 것으로 예상되는 특정 이름의 메시지 큐에 접근합니다. `O_WRONLY` 플래그는 이 클라이언트가 큐에 메시지를 쓸 수만 있도록 지정합니다. 준비된 메시지 버퍼와 그 크기를 `mq_send` 함수에 전달하여 큐에 메시지를 넣습니다. 메시지 전송 후, 클라이언트는 보낸 메시지를 화면에 출력하고 `mq_close`를 호출하여 메시지 큐와의 연결을 종료합니다.
 */