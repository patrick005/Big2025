#include "queue.h"
#include <cassert>

const int Queue::QUEUE_SIZE = 100; 

Queue::Queue(int size) // -> pArr_, size_ 없어짐, arr_로 대체
// : pArr_(new int[size]), size_(size), front_(0), rear_(0) {
    : arr_(size), front_(0), rear_(0) {
    // assert(pArr_ );
}

Queue::~Queue(){
    // delete [] pArr_; // pArr 삭제 및 array.h에서의 소멸자로 인해서 자동 삭제로 제거
}

bool Queue::isEmpty() const{
    return front_ == rear_;
}
bool Queue::isFull() const{
    // return rear_ == size_;
    return rear_ == arr_.size();
}
int Queue::size() const{
    // return size_;
    return arr_.size();
}
int Queue::avab() const{
    // return size_ - rear_;
    return arr_.size() - rear_;
}

void Queue::push(int data){
    // assert(rear_ != size_);
    // pArr_[rear_] = data;
    arr_[rear_] = data;
    ++rear_;
}

int Queue::pop(){
    assert(front_ != rear_);

    int index = front_;
    ++front_;
    // return pArr_[index];
    return arr_[index];

}
