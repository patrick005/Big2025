//ex16_2_finalModernExample.cpp
/* 
목표              : STL과 스마트포인터를 사용해서 데이터베이스 엔진 만드세요.
스마트 포인터 활용 : shared_ptr, unique_ptr
쓰레드 활용        : multithread, mutex, atomic -> 내부 동기화 위한 락 구조 설계
데이터 삽입        : insert(key(int), value(string));
테이터 검색        : find(key);
데이터 삭제        : remove(key);
클래스 명          : DataBase
저장용 컨테이너    : 참조에 특화된 unordered_map 사용

시간 남는 사람      :컬럼 추가(타입 지정) .. 도전 할 사람만 -> 삽입값에 대해 템플릿화

강사님 버전
*/
#include <iostream>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>
#include <memory>
#include <mutex>
#include <shared_mutex> //
// #include <future>
// #include <atomic>
// #include <chrono>
// #include <algorithm>
// #include <any>
// #include <typeinfo>

using namespace std;
using namespace chrono_literals;

class DataBase{
private:
    unordered_map<int, shared_ptr<string>> db;
    mutable shared_mutex mtx;

public:

void insert(int key , const string &value){ // 데이터베이스 데이터 삽입
        unique_lock lock(mtx);
        db[key] = make_shared<string>(value);
    }
    
    shared_ptr<string> find(int key) const{   // 데이터베이스 특정 데이터 출력
        shared_lock lock(mtx);          // 여러명이 찾을 수도 있도록 해야함
        auto it = db.find(key);
        return (it != db.end()) ? it->second : nullptr;
    }

    void remove(int key){  // 데이터베이스 특정 데이터 삭제
        unique_lock lock(mtx);
        db.erase(key);
    }

    void print_all() const { // 데이터베이스 전체 출력
        shared_lock lock(mtx);
        for(const auto &[key, value] : db){
            cout << key << " : " << *value << endl;
        }
    }
};

void threadTask(DataBase &db, int id){
    for(int i = 0; i < 5; ++i){
        db.insert(id * 10 + i, "Data from main" + to_string(id));
        this_thread::sleep_for(50ms);
    }
}

int main()
{
    DataBase db;
    vector<thread> threads;
    for (int i = 0; i < 20; ++i){
        threads.emplace_back(threadTask, ref(db), i);
    }
    // db.remove(4);
    // db.remove(8);
    
    // cout << "find 3 : " << db.find(3) << endl;

    for(auto &t : threads){
        t.join();
    }
    // db.remove(4);
    // db.remove(8);
    
    // cout << "find 142 : " << db.find(142) << endl;
    db.print_all();
    return 0;
}