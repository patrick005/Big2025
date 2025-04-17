// ./cpp/stackCpp/stack.cpp
#include "stack.h"
#include <cstring>
#include <cassert>

Stack::Stack(int size/*, int eleSize*/){
    // this->pArr = malloc(eleSize * size);
    this->pArr = new int[size];
    assert(this->pArr != NULL);//NULl대비
    this->size = size;
    this->tos = 0;
}

Stack::~Stack(){
    delete [] this->pArr;
}

void Stack::push(int data){
    assert(this->tos != this->size);
    this->pArr[this->tos] = data;
    ++this->tos;
}
int Stack::pop(){
    assert(this->tos != 0);

    --this->tos;
    return this->pArr[this->tos];
}



