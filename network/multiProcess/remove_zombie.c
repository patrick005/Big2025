//remove_zombie.c
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

void readChildprocCallback(int sig);

int main(){
    struct sigaction act; // 시그널 액션 구조체 선언
    act.sa_handler = readChildprocCallback; // 시그널 처리 함수 지정
    sigemptyset(&act.sa_mask); // 시그널 마스크 초기화
    act.sa_flags = 0; // 플래그 설정 (기본 동작)
    sigaction(SIGCHLD, &act, 0); // SIGCHLD 시그널에 대한 액션 설정

    pid_t pid = fork(); // 첫 번째 자식 프로세스 생성
    int status; // 자식 프로세스의 종료 상태 저장 변수 선언

    if (pid == 0){ // 자식1 프로세스 영역
        puts("안녕! 나는 자식 프로세스야!!");
        sleep(10); // 10초 동안 대기
        return 12; // 종료 상태 값 12 반환
    }else{ // 부모 프로세스 영역
        printf("자식1 프로세스 ID: %d \n", pid);
        pid = fork(); // 두 번째 자식 프로세스 생성
        if (pid == 0){ // 자식2 프로세스 영역
            puts("안녕, 나는 두번째 자식 프로세스야!!");
            sleep(2); // 2초 동안 대기
            exit(24); // 종료 상태 값 24로 종료
        }else{ // 부모 프로세스 영역
            printf("자식2 프로세스 ID: %d \n", pid);
            for (int i = 0; i < 5; ++i){ // 5번 반복
                puts("sleep 3초.");
                sleep(3); // 3초 동안 대기
            }
        }
    }
    return 0; // 부모 프로세스 종료
}

void readChildprocCallback(int sig){
    int status; // 자식 프로세스의 종료 상태 저장 변수 선언
    pid_t id = waitpid(-1, &status, WNOHANG); // 종료된 자식 프로세스 회수 (non-blocking)
    if (WIFEXITED(status)){ // 자식 프로세스가 정상 종료되었는지 확인
        printf("프로세스 제거 id: %d \n", id); // 제거된 자식 프로세스 ID 출력
        printf("자식이 보낸 번호: %d \n", WEXITSTATUS(status)); // 자식 프로세스가 반환한 종료 상태 값 출력
    }
}

/**
 * **컴포넌트:** 좀비 프로세스 제거
 *
 * **목표:** 부모 프로세스가 자식 프로세스의 종료를 감지하고 회수하여 좀비 프로세스가 남지 않도록 처리하는 프로그램임.
 *
 * **프로세스:**
 * 1. `sigaction()` 함수를 사용하여 `SIGCHLD` 시그널 발생 시 `readChildprocCallback` 함수를 호출하도록 설정함. `SIGCHLD` 시그널은 자식 프로세스가 종료될 때 부모 프로세스에게 전달됨. `WNOHANG` 플래그를 사용하여 `waitpid()` 함수를 비블로킹 모드로 설정하여 부모 프로세스가 자식 프로세스 종료를 기다리지 않고 자신의 작업을 계속 수행하도록 함.
 * 2. `fork()` 함수를 두 번 호출하여 두 개의 자식 프로세스를 생성함.
 * 3. 첫 번째 자식 프로세스는 "안녕! 나는 자식 프로세스야!!" 메시지를 출력하고 10초 동안 대기한 후 종료 상태 값 12를 반환하며 종료됨.
 * 4. 두 번째 자식 프로세스는 "안녕, 나는 두번째 자식 프로세스야!!" 메시지를 출력하고 2초 동안 대기한 후 종료 상태 값 24로 강제 종료됨.
 * 5. 부모 프로세스는 각 자식 프로세스의 ID를 출력하고, 5번 반복하며 3초씩 대기함.
 * 6. 자식 프로세스가 종료되면 `SIGCHLD` 시그널이 부모 프로세스에게 전달되고, 등록된 `readChildprocCallback` 함수가 실행됨.
 * 7. `readChildprocCallback` 함수 내에서 `waitpid()` 함수를 호출하여 종료된 자식 프로세스를 회수하고, `WIFEXITED()` 매크로를 사용하여 자식 프로세스가 정상 종료되었는지 확인한 후, 회수된 자식 프로세스의 ID와 종료 상태 값을 출력함. `WNOHANG` 플래그 덕분에 부모 프로세스는 `waitpid()` 호출에 블로킹되지 않고 계속 자신의 작업을 수행할 수 있음.
 * 8. 부모 프로세스는 5번의 3초 대기 루프를 완료한 후 종료됨.
 *
 * **기능:**
 * - 자식 프로세스 생성 및 실행: 두 개의 자식 프로세스를 생성하여 각자 다른 작업을 수행하도록 함.
 * - 좀비 프로세스 방지: 자식 프로세스 종료 시 발생하는 `SIGCHLD` 시그널을 감지하고 `waitpid()` 함수를 호출하여 종료된 자식 프로세스를 회수함으로써 좀비 프로세스가 남는 것을 방지함.
 * - 자식 프로세스 종료 정보 확인: 회수된 자식 프로세스의 ID와 종료 상태 값을 확인하고 출력함.
 *
 * **개념:**
 * - **프로세스(Process):** 실행 중인 프로그램의 인스턴스임.
 * - **자식 프로세스(Child Process):** `fork()` 함수를 통해 부모 프로세스로부터 복제되어 생성된 프로세스임.
 * - **좀비 프로세스(Zombie Process):** 종료되었지만 부모 프로세스가 회수하지 않아 시스템에 남아있는 프로세스임.
 * - **시그널(Signal):** 운영체제가 프로세스에게 특정 이벤트 발생을 알리는 메커니즘임.
 * - **SIGCHLD:** 자식 프로세스가 종료될 때 부모 프로세스에게 전달되는 시그널임.
 * - **sigaction():** 시그널 처리 방식을 설정하는 시스템 호출임.
 * - **waitpid():** 자식 프로세스의 종료를 기다리고, 종료된 자식 프로세스의 정보를 얻는 시스템 호출임.
 * - **WNOHANG:** `waitpid()` 함수의 옵션으로, 자식 프로세스가 종료되지 않았으면 즉시 반환하도록 함 (non-blocking).
 * - **WIFEXITED():** `waitpid()` 함수의 반환 상태를 확인하여 자식 프로세스가 정상적으로 종료되었는지 여부를 반환하는 매크로임.
 * - **WEXITSTATUS():** 정상 종료된 자식 프로세스가 `exit()` 또는 `return` 문을 통해 반환한 종료 상태 값을 얻는 매크로임.
 */