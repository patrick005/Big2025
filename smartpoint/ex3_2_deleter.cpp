//ex3_2_deleter.cpp
#include <cstdio>
#include <memory>
#include <iostream>
using namespace std;

class FileCloser{
public:
    void operator()(FILE *fp){
        if (fp){
            cout << "fclose 동작" << endl;
            fclose(fp);
        }
    }
};

void useUnique(unique_ptr<FILE, FileCloser> ptr){
    cout << "fp를 받아서 사용한 함수" << endl;
}

int main(){
    // unique_ptr<FILE, FileCloser> filePtr(fopen("/home/aa/Big2025/smartpoint/1000.txt", "r"));
    auto fp = fopen("/home/aa/Big2025/smartpoint/1000.txt", "r"); // 위에 줄 두줄로 풀어서 사용
    unique_ptr<FILE, FileCloser> filePtr(fp);
    
    // ...file 관련된 코드1
    // ...file 관련된 코드1
    // fclose(fp); ---> 필요없음. operator에서 동작을 끝내면서 작용함

    useUnique(move(filePtr));

    cout << "main 함수의 끝" << endl;
    return 0;
}


/*
1000개짜리 파일 열었다 닫았다 테스트
동작 순서는 
main 시작 -> 파일 열기 -> unique_ptr 생성 -> useUnique 함수 호출 (파일 소유권 이동) -> useUnique 함수 실행 
    -> useUnique 함수 종료 (FileCloser::operator() 호출 및 파일 닫기) -> main 종료

*/