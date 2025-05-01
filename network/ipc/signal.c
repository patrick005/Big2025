//signal.c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeoutCallback(int sig);
void keycontrolCallback(int sig);

int main(){
    signal(SIGALRM, timeoutCallback);     // SIGALRM 시그널 발생 시 timeoutCallback 함수 호출
    signal(SIGINT, keycontrolCallback);    // SIGINT 시그널 발생 시 keycontrolCallback 함수 호출
    alarm(2);                             // 2초 후에 SIGALRM 시그널 발생 예약

    for (int i = 0; i < 10; i++){         // 10번 반복
        puts("wait...");
        sleep(100);                       // 100초 동안 대기 (시그널에 의해 일찍 깨어날 수 있음)
    }
    return 0;
}

void timeoutCallback(int sig){
    if(sig == SIGALRM){                 // 받은 시그널이 SIGALRM인지 확인
        puts("Time out!");             // 타임아웃 메시지 출력
    }
    alarm(2);                         // 다시 2초 후에 SIGALRM 시그널 발생 예약
}

void keycontrolCallback(int sig){
    if (sig == SIGINT){                  // 받은 시그널이 SIGINT인지 확인 (Ctrl + C)
        puts("Ctrl + C pressed!");      // Ctrl + C 입력 메시지 출력
    }
}

/**
 * **컴포넌트:** 기본 시그널 처리 데모
 *
 * **목표:** `signal` 함수를 사용하여 `SIGALRM` (타이머) 시그널과 `SIGINT` (Ctrl + C) 시그널에 대한 사용자 정의 콜백 함수를 등록하고, 각 시그널이 발생했을 때 해당 콜백 함수가 실행되는 방식을 보여줍니다.
 *
 * **기능:**
 * - `timeoutCallback` 함수는 `SIGALRM` 시그널을 받으면 "Time out!" 메시지를 출력하고, `alarm(2)`를 호출하여 2초 후에 또 다른 `SIGALRM` 시그널을 예약합니다. 이는 주기적인 알람을 설정하는 방식입니다.
 * - `keycontrolCallback` 함수는 `SIGINT` 시그널을 받으면 "Ctrl + C pressed!" 메시지를 출력합니다. `SIGINT` 시그널은 일반적으로 사용자가 터미널에서 Ctrl + C 키를 눌렀을 때 발생합니다.
 * - `main` 함수에서는 `signal()` 함수를 사용하여 각 시그널과 콜백 함수를 연결합니다.
 * - `alarm(2)` 함수를 호출하여 프로그램 시작 2초 후에 첫 번째 `SIGALRM` 시그널을 발생시키도록 예약합니다.
 * - `for` 루프 내에서 `sleep(100)`을 호출하여 100초 동안 대기하지만, 실제로 예약된 `SIGALRM` 시그널이 2초마다 발생하거나 사용자가 Ctrl + C를 누르면 해당 콜백 함수가 실행되어 `sleep` 함수가 인터럽트될 수 있습니다.
 *
 * **동작 방식:**
 * 프로그램이 시작되면 2초 후에 `SIGALRM` 시그널이 발생하여 `timeoutCallback`이 실행되고 "Time out!" 메시지가 출력되며, 2초 후의 알람이 다시 설정됩니다. 이 과정이 반복되어 대략 2초마다 "Time out!" 메시지가 출력됩니다. 동시에, 사용자가 터미널에서 Ctrl + C 키를 누르면 `SIGINT` 시그널이 발생하여 `keycontrolCallback` 함수가 실행되고 "Ctrl + C pressed!" 메시지가 출력됩니다. `signal()` 함수는 기본적인 시그널 처리 메커니즘을 제공하며, 특정 시그널이 발생했을 때 미리 정의된 함수를 실행하도록 설정하는 데 사용됩니다.
 */