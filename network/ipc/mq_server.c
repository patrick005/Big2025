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
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10; // 저장 가능한 큐 버퍼 크기 
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;
    
    mqd_t mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, QUEUE_PERMS, &attr); // 비트로 옵션을 받지만 복잡한 경우 구조체 형식으로 받음

    char buffer[MAX_MSG_SIZE + 1];
    ssize_t bytes_read;

    for (int i = 0; i < 5; i++){
        bytes_read = mq_receive(mq, buffer, MAX_MSG_SIZE + 1, NULL);
        buffer[bytes_read] = '\0';
        printf("서버에서 받은 메세지: %s\n", buffer);
    }


    mq_close(mq);
    mq_unlink(QUEUE_NAME);

    return 0;
}


/*
위치: /dev/mqueue/myqueue
echo 'form cli' >> /dev/mqueue/myqueue 버퍼형식이 아니라 안뜰거임
cat myqueue하면 여기 쌓인 메세지 정보가 출력

for문을 돌려서 여러개의 정보를 수용하게 묶어두고 ctrl + c로 강제종료하면 /dev/mqueue/myqueue에 쌓이는 것을 cat으로 확인할 수 있음
여기서 다시 서버를 돌리면 쌓인거에 대한 일괄적인 처리가 시작이 됨

*/