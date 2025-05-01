//ex11_nullptr.cpp
#include <iostream>

void func(int){std::cout << "int\n"; }
void func(int *){std::cout << "pointer\n"; }
void func(long){std::cout << "long\n"; }

int main(){

    int *ptr = nullptr; // 초기화
    int *fp;
    if (ptr == nullptr){
        std::cout << "Null pointer" << std::endl;
    }

    func(0L);                                       //long 명시해둠
    func(1);                                        //int
    // func(NULL); //널포인터로 안 가짐                 //long 취급이나 passing NULL to non-pointer argument 1 of ‘void func(long int)’ [-Wconversion-null]로 무시 된것을 볼 수 있음
    func(nullptr); //->이건 가짐                    //포인터
    func(ptr); // 선언해서 이것도 널의 포인터로 가짐  //포인터
    func(fp);                                       //포인터

    return 0;
}


/*c에서는 NULL이 정수 0으로 정의되어 있어 함수 오버로딩 시 모호성을 야기할 수 있었지만
cpp에서는 nullptr이 명확한 널 포인터 타입으로 도입되어 이러한 모호성을 해결하고
타입 안전성을 높였습니다. 이 코드는 nullptr의 이러한 특징을 확인하기 위해 작성된 코드임*/