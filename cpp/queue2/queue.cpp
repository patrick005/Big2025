#include "queue.h"
#include <cassert>

// const int QUEUE_SIZE = 100;
const int Queue::QUEUE_SIZE = 100; // static멤버함수로 변경하면서 앞에 Queue::가 붙음

Queue::Queue(int size)
: pArr_(new int[size]), size_(size), front_(0), rear_(0) {
    assert(pArr_ );
}

Queue::~Queue(){
    delete [] pArr_;
}

bool Queue::isEmpty() const{
    return front_ == rear_;
}
bool Queue::isFull() const{
    return rear_ == size_;
}
int Queue::size() const{
    return size_;
}
int Queue::avab() const{
    return size_ - rear_;
}

void Queue::push(int data){
    assert(rear_ != size_);
    pArr_[rear_] = data;
    ++rear_;
}

int Queue::pop(){
    assert(front_ != rear_);

    int index = front_;
    ++front_;
    return pArr_[index];

}
