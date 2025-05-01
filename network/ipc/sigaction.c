//sigaction.c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void timeoutCallback(int sig);

int main(){
    // signal(SIGALRM, timeoutCallback);     // SIGALRM 시그널 발생 시 timeoutCallback 호출 (단순 시그널 처리)
    struct sigaction act; // 시그널 액션 구조체
    act.sa_handler = timeoutCallback; // 시그널 처리 함수 지정
    sigemptyset(&act.sa_mask); // 시그널 마스크 초기화 (다른 시그널 블록 안 함)
    act.sa_flags = 0; // 플래그 설정 (기본 동작 사용)
    sigaction(SIGALRM, &act, 0); // SIGALRM 시그널에 대한 액션 설정

    alarm(2); // 2초 후에 SIGALRM 시그널 발생 예약

    for (int i = 0; i < 10; i++){ // 10번 반복
        puts("wait...");
        sleep(100); // 100초 동안 대기 (실제로는 시그널 때문에 일찍 깨어남)
    }
    return 0;
}

void timeoutCallback(int sig){
    if(sig == SIGALRM){ // 받은 시그널이 SIGALRM인지 확인
        puts("Time out!"); // 타임아웃 메시지 출력
    }
    alarm(2); // 다시 2초 후에 SIGALRM 시그널 발생 예약 (반복적인 알람)
}

/**
 * **컴포넌트:** 시그널 처리 데모
 *
 * **목표:** `sigaction` 함수를 사용하여 `SIGALRM` 시그널에 대한 사용자 정의 콜백 함수를 등록하고, 주기적으로 타임아웃 이벤트를 발생시켜 처리하는 방법을 보여줍니다.
 *
 * **기능:**
 * - `timeoutCallback` 함수를 정의하여 `SIGALRM` 시그널이 발생했을 때 "Time out!" 메시지를 출력하고, `alarm(2)`를 호출하여 2초 후에 또 다른 `SIGALRM` 시그널을 예약합니다. 이는 주기적인 타이머 역할을 합니다.
 * - `main` 함수에서는 `struct sigaction`을 설정하여 `SIGALRM` 시그널이 발생하면 `timeoutCallback` 함수가 호출되도록 합니다. `sigemptyset`은 시그널 처리 중에 다른 시그널이 블록되지 않도록 초기화합니다.
 * - `alarm(2)` 함수를 호출하여 프로그램 시작 2초 후에 첫 번째 `SIGALRM` 시그널을 발생시키도록 예약합니다.
 * - `for` 루프 내에서 `sleep(100)`을 호출하여 100초 동안 대기하지만, 실제로 `SIGALRM` 시그널이 발생하면 `timeoutCallback`이 실행되고 `sleep` 함수는 인터럽트되어 루프가 계속됩니다.
 *
 * **동작 방식:**
 * 프로그램이 시작되면 2초 후에 `SIGALRM` 시그널이 발생합니다. 이 시그널을 받으면 `timeoutCallback` 함수가 실행되어 "Time out!" 메시지를 출력하고, 다시 `alarm(2)`를 호출하여 2초 후에 또 다른 `SIGALRM` 시그널을 예약합니다. 이 과정이 반복되면서 "Time out!" 메시지가 대략 2초마다 출력됩니다. `main` 함수의 `sleep(100)`은 시그널에 의해 인터럽트되므로, 프로그램은 100초를 기다리지 않고 다음 루프를 진행합니다. 따라서 이 프로그램은 주기적인 알람 메커니즘을 사용하여 특정 작업을 주기적으로 수행하거나 타임아웃을 처리하는 기본적인 방법을 보여줍니다. `signal()` 함수를 사용하는 방식과 `sigaction()` 함수를 사용하는 방식의 차이를 보여주며, `sigaction()`이 더 강력하고 유연한 시그널 처리 방식을 제공합니다.
 */