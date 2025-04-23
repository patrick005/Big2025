//ex3_deleter.cpp
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

int main(){
    // unique_ptr<FILE, FileCloser> filePtr(fopen("/home/aa/Big2025/smartpoint/1000.txt", "r"));
    auto fp = fopen("/home/aa/Big2025/smartpoint/1000.txt", "r"); // 위에 줄 두줄로 풀어서 사용
    unique_ptr<FILE, FileCloser> filePtr(fp);
    
    // ...file 관련된 코드1
    // ...file 관련된 코드1
    // fclose(fp); ---> 필요없음. operator에서 동작을 끝내면서 작용함

    return 0;
}


/*
1000개짜리 파일 열었다 닫았다 테스트

*/