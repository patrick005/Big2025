//ex16_finalModernExample.cpp
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
*/
#include <iostream>
#include <memory>
#include <future>
#include <mutex>
#include <atomic>
#include <unordered_map>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include <any>
#include <typeinfo>

using namespace std;
using namespace chrono_literals;

class DataBase{
private:
    unordered_map<unique_ptr<int>, shared_ptr<string>> row_;
    mutex mtx_;

public:
    DataBase(){} //기본 생성자
    ~DataBase(){} // 소멸자

    void view_all_db(){ // 데이터베이스 전체 출력
        lock_guard<mutex> lock(mtx_);
        vector<pair<int, string>> sortingArray;
        for (const auto& pair : row_) {
            sortingArray.push_back({*pair.first, *pair.second});
        }
        sort(sortingArray.begin(), sortingArray.end(), [](const pair<int, string>& a, const pair<int, string>& b){
            return a.first < b.first;
        });
        for (const auto& item : sortingArray) {
            cout << item.first << " : " << item.second << endl;
        }
        return;
    }

    void insert_query(int key , string value){ // 데이터베이스 데이터 삽입
        lock_guard<mutex> lock(mtx_);
        unique_ptr<int> key_ptr = make_unique<int>(key);
        shared_ptr<string> value_ptr = make_shared<string>(value);
        row_[move(key_ptr)] = move(value_ptr);
    }

    vector<string> find_query(int findKey){ // 데이터베이스 특정 데이터 출력
        lock_guard<mutex> lock(mtx_);
        vector<string> values;
        for (const auto& pair : row_) {
            if (*pair.first == findKey) {
                values.push_back(*pair.second);
                cout << *pair.first << "번째 데이터의 값은 " << *pair.second << "입니다." << endl;
            }
        }
        return values;
    }

    void remove_query(int rmKey){  // 데이터베이스 특정 데이터 삭제
        lock_guard<mutex> lock(mtx_);
        for (auto it = row_.begin(); it != row_.end(); ++it) {
            if (*(it->first) == rmKey) {
                cout << *(it->first) << "번째 데이터가 삭제되었습니다." << endl;
                row_.erase(it);
                return; // Assuming keys are unique, we can return after the first match
            }
        }
    }
};

int main()
{
    DataBase mydb;

    mydb.insert_query(1 , "1장 sql");
    mydb.insert_query(2 , "2장 c언어");
    mydb.insert_query(3 , "3장 atmega128");
    mydb.insert_query(4 , "프로젝트");
    mydb.insert_query(5 , "4장 rasspberrPi4");
    mydb.insert_query(6 , "5장 cpp언어");
    // mydb.view_all_db();
    mydb.find_query(6);
    mydb.remove_query(4);
    mydb.view_all_db();
    return 0;
}