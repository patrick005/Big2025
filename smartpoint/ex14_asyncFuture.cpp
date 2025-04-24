//ex14_asyncFuture.cpp
#include <iostream>
#include <chrono>
#include <future>
using namespace std;

// 오래 걸리는 더하기 함수 (비동기 실행 예시)
int slowAdd(int a, int b){
    this_thread::sleep_for(chrono::seconds(2));
    return a + b;
}

int main(){
    // async: slowAdd 함수를 새로운 스레드에서 비동기적으로 실행 시작
    // future<int> result: async의 실행 결과를 담을 미래(future) 객체
    future<int> result = async(slowAdd, 2, 3);
    cout << "계산 중 ..." << endl;

    // result.get(): future 객체에서 비동기 작업의 결과(int)를 가져옴
    // get()은 결과가 준비될 때까지 현재 스레드를 '대기'시킴 (동기적인 기다림)
    cout << "결과 : " << result.get() << endl;


    return 0;
}

/*
23버전부터 사용 가능한 기능이라 cmake가 아닌 명령어를 통해 컴파일 및 실행
g++ -o test -std=c++23 ex14_asyncFuture.cpp
./test

**async (비동기 실행):**
- 'async'는 함수를 **새로운 스레드**에서 독립적으로 실행하도록 요청하는 기능입니다.
- 마치 '요리사에게 주문을 넣고 다른 일을 하는 것'과 같습니다. 메인 요리사는 다른 작업을 계속할 수 있고, 주문한 요리는 나중에 준비되면 받을 수 있습니다.
- `async(함수, 인자1, 인자2, ...)` 형태로 사용합니다.

**future (미래):**
- 'future'는 비동기적으로 실행된 작업의 **'미래의 결과'**를 담는 객체입니다.
- '요리 주문서'와 같습니다. 주문서 자체는 아직 음식이 아니지만, 나중에 음식이 나오면 그 주문서를 통해 음식을 받을 수 있습니다.
- `async`를 호출하면 `future` 객체가 반환됩니다.

**result.get():**
- `future` 객체의 `.get()` 함수는 비동기 작업의 **실제 결과**를 가져오는 역할을 합니다.
- '주문한 음식이 나오면 받아서 먹는 행위'와 같습니다. 만약 음식이 아직 준비되지 않았다면, `.get()`을 호출한 사람은 음식이 나올 때까지 **기다립니다** (여기서 잠깐 동기적인 대기가 발생합니다).

**핵심:**
- `async`로 오래 걸리는 작업을 **분리**해서 실행하면 메인 프로그램이 멈추지 않고 다른 작업을 할 수 있습니다.
- `future`를 통해 그 **결과를 나중에 안전하게** 받아올 수 있습니다. `.get()`을 호출할 때까지 결과가 준비되지 않았다면 기다리게 됩니다.
*/