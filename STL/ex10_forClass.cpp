//ex10_forClass.cpp
#include <iostream>
#include <cstddef>

template <typename T, std::size_t N>
class MyContainer{
private:
    T data_[N];
public:
    MyContainer(){
        for (std::size_t i = 0; i < N; i++){
            data_[i] = static_cast<T>(i + 1);
        }
    }
    class Iter{
    private:
        T *ptr;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T *;
        using reference = T &;

        explicit Iter(T *p) : ptr(p) {}
        reference operator*() const { return *ptr; }
        pointer operator->() { return ptr;}
        Iter& operator++(){     // 전위
            ++ptr;
            return *this;
        }
        Iter operator++(int){
            Iter temp = *this;
            ++(this);
            return temp;
        }
        friend bool operator==(const Iter& a, const Iter &b){ // == 논리연산
            return a.ptr == b.ptr;
        }
        friend bool operator!=(const Iter& a, const Iter &b){ // != 논리 연산
            return a.ptr != b.ptr;
        }
    };
    Iter begin() { return Iter(data_); }
    Iter end() { return Iter(data_ + N); }
};

using namespace std;
int main(){
    

    MyContainer<int, 10> container;

    for (auto v : container){
        cout << v << " ";
    }
    cout << endl;

    return 0;
}


/*
MyContainer 클래스는 템플릿을 사용하여 임의 타입 T와 크기 N을 갖는 배열을 내부적으로 관리하며, 생성 시 각 요소를 1부터 N까지의 값으로 초기화합니다.
MyContainer 내부에 정의된 Iter 클래스는 사용자 정의 반복자로서, MyContainer 객체의 요소들을 순회할 수 있도록 begin()과 end() 메서드를 통해 시작과 끝 반복자를 제공합니다.
main 함수에서는 MyContainer<int, 10> 객체를 생성하고, 범위 기반 for 루프를 사용하여 컨테이너의 모든 요소를 순차적으로 출력합니다.


C++11에서 도입된 범위 기반 for 루프

*/