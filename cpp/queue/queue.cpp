#include "queue.h"
// #include <assert.h>
// #include <stdlib.h>
#include <cassert>
#include <cstdio>

// void initQueue(Queue *this, int size){
Queue::Queue(int size){
    // this->pArr = malloc(sizeof(int)*size);
    this->pArr = new int[size];
    assert(this->pArr != NULL);
    this->size = size;
    
    this->front = this->rear = 0;
}

// void cleanupQueue(){
Queue::~Queue(){
    // free(this->pArr);
    delete [] this->pArr;
}

void Queue::push(int data){
    assert(this->rear != this->size);

    this->pArr[this->rear] = data;
    ++this->rear;
}

int Queue::pop(){
    assert(this->front != this->rear);

    int index = this->front;
    ++this->front;
    return this->pArr[index];

}
