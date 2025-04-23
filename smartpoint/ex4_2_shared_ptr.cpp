//ex4_2_shared_ptr.cpp
#include <memory>
#include <iostream>
using namespace std;

void useShared(shared_ptr<int> ptr){
    cout << "넘겨 받은 ptr의 use cout : " << ptr.use_count() << endl;
}

int main(){
    auto a = make_shared<int>(100); 
    auto b = a; // 포인터에 대한 참조가 생김
    auto c = a;
    
    // useShared(a);
    useShared(move(a));
    cout << "a use_cout: " << a.use_count() << endl;
    cout << "b use_cout: " << b.use_count() << endl;

    return 0;
}


/*
함수로 넘기는 버전
함수로 값 복사하여 넘기는 버전 (useShared(a); 주석 해제 시)
함수 내부에서 넘겨받은 ptr의 use count는 4가 되지만, 함수 종료 후 a, b 개별 출력시에는 다시 3이 됨

move로 소유권을 옮기는 버전 (useShared(move(a)); 실행 시)
move를 통해 a의 소유권이 useShared 함수로 이동하여 함수 내부에서 참조 카운트가 4가 됨
함수 종료 후 a는 nullptr이 되고, b와 c는 여전히 같은 객체를 공유하므로 use count는 2가 됨
*/