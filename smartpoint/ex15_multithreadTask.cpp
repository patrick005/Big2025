//ex15_multithreadTask.cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <functional>
#include <vector>
#include <atomic>
#include <condition_variable>

using namespace std;
using namespace chrono_literals;
// this_thread::sleep_for(chrono::seconds(1)); 이거 약식으로 사용가능하게 하는 네임스페이스

class TaskQueue{
private:
    queue<function<void()>> tasks;
    mutex mtx;
    condition_variable cv;
    vector<thread> workers;
    atomic<bool> stop{false}; // mutex랑 비슷한 일 , 스레드가 돌아갈때 실행의 단위로 묶음, 뮤텍은 블록 단위라면 이건 코드 줄 단위로 제어 가능

public:
    TaskQueue(size_t thread_count){
        for (size_t i = 0; i < thread_count; i++){
            workers.emplace_back([this](){
                while (true){
                    function<void()> task;
                    { //블록으로 써먹기 위한 중괄호
                        unique_lock<mutex> lock(mtx);
                        cv.wait(lock, [this](){
                            return stop || !tasks.empty();
                        });
                        if(stop &&tasks.empty()){
                            return;
                        }
                        task = move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            });
        }
    }
    void enqueue(function<void()> task){ // 등록하는 놈
        {
            lock_guard<mutex> lock(mtx);
            tasks.push(move(task));
        }
        cv.notify_one();
    }
    ~TaskQueue(){ // 소멸자
        stop = true;
        cv.notify_all();
        for(auto &t : workers){
            t.join();
        }
    }
};

int main(){
    TaskQueue queue(4);
    for (int i = 0; i < 10; ++i){
        queue.enqueue([i](){
            cout << " 작업 " << i << " 시작 " << endl;
        });
    }
    // this_thread::sleep_for(chrono::seconds(1));
    this_thread::sleep_for(1s); // 1초 대기

    return 0;
}