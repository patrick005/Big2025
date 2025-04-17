#include "stack.h"
#include <cassert>
#include <cstdio>

// const int STACK_SIZE = 100;
const int Stack::STACK_SIZE = 100;

// Stack::Stack(int size)
// : pArr_(new int[size]), size_(size), tos_(0)  //요래 쓰면 this-> 대신 _만 뒤에 붙이면 됨
// {
//     // this->pArr = new int[size];
//     // // assert(this->pArr != NULL);//NULl대비
//     // this->size = size;
//     // this->tos = 0;
// }
Stack::Stack(int size)
: arr_(size), tos_(0){//has-a 관계도 일종의 상속이다
    
}
Stack::~Stack(){ //Array쪽의 소멸자에도 delete가 있고 거기서 처리가 될거다
    // delete [] pArr_;
}

bool Stack::isEmpty() const{
    return tos_ == 0;
}
bool Stack::isFull() const{
    // return tos_ == size_;
    return tos_ == arr_.size;
}
int Stack::size() const{
    // return size_;
    return arr_.size();
}
int Stack::avab() const{
    // return size_ - tos_;
    return arr_.size() - tos;
}

void Stack::push(int data){
    assert(!this->isFull());

    // pArr_[tos_] = data;
    arr_[tos_] = data;
    ++tos_;
}

int Stack::pop(){
    assert(!this->isEmpty());

    --tos_;
    // return pArr_[tos_];
    return arr_[tos_];
}

//stack3은 has-a관계를 이용하여 파일을 구축함
//stack has a array?
/*
~/Big2025/cpp/stack3$ g++ -o testStack  main.o stack.o array.o
~/Big2025/cpp/stack3$ ./testStack 

*/