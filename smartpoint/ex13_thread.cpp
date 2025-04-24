//ex13_thread.cpp
#include <iostream>
#include <thread>
#include <mutex> // mutually exclusive 상호 배제한다는 단어의 약어
// 여러 스레드에서 변수 하나에 접근을 하면 문제가 생기니 하나의 스레드가 점유하는 방식으로 접근이 가능하게 해놓은 기능

using namespace std;

int counter = 0;
mutex mtx;

void increment(){
    for (int i = 0; i < 1000; ++i){
        lock_guard<mutex> lock(mtx); // 뮤텍스를 잠금 (RAII 방식으로 자동 해제 보장)
        ++counter;
        
    }
}

int main(){                 // main 스레드 시작
    thread t1(increment);     // t1 스레드 생성 및 increment 함수 실행 시작 (main 스레드와 병행 가능)
    thread t2(increment);     // t2 스레드 생성 및 increment 함수 실행 시작 (main, t1 스레드와 병행 가능)
    // 이 시점에서 main, t1, t2 세 개의 스레드가 동시에 실행될 수 있습니다.

    t1.join();      // main 스레드는 t1 스레드의 종료를 기다림 (t1 스레드가 increment 함수 완료까지 블로킹)
    // t1 스레드 종료 후 이 지점 도달
    t2.join();      // main 스레드는 t2 스레드의 종료를 기다림 (t2 스레드가 increment 함수 완료까지 블로킹)
    // t2 스레드 종료 후 이 지점 도달
    // execution - main thread는 t1, t2 스레드가 모두 끝날 때까지 대기한 후 아래 코드 실행

    cout << "최종 카운터 값: " << counter << endl;

    return 0; // main 스레드 종료 및 프로그램 종료
}