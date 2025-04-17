// 
#include <cassert>
#include "stack.h"

// const int STACK_SIZE = 100;
const int Stack::STACK_SIZE = 100;

Stack::Stack(int size)
: pArr_(new int[size]), size_(size), tos_(0)  //요래 쓰면 this-> 대신 _만 뒤에 붙이면 됨
{
    // this->pArr = new int[size];
    assert(pArr_ /*!= NULL*/); //NULl대비
    // this->size = size;
    // this->tos = 0;
}

Stack::~Stack(){ 
    delete [] pArr_;
}

bool Stack::isEmpty() const{
    return tos_ == 0;
}
bool Stack::isFull() const{
    return tos_ == size_;
}

int Stack::size() const{
    return size_;
}
int Stack::avab() const{
    return size_ - tos_;
}

void Stack::push(int data){
    assert(!this->isFull());
    pArr_[tos_] = data;
    ++tos_;
}

int Stack::pop(){
    assert(!this->isEmpty());

    --tos_;
    return pArr_[tos_];
}
