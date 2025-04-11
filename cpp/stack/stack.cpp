//c의 전역함수를 cpp의 멤버함수로 변경하면서 구조체에 묶임
#include "stack.h"
// #include <stdlib.h> -> malloc 미사용으로 인한 주석처리
// #include <cstdlib>
// #include <assert.h>
#include <cassert>
// #include <stdio.h>
#include <cstdio>

// void initStack(Stack *this, int size){
// void Stack::initStack(int size){
Stack::Stack(int size){
    // this->pArr = (int *)malloc(sizeof(int)*size); // c랑 다르게 cpp는 동적할당에 타입캐스팅이 필요함
    this->pArr = new int[size];
    assert(this->pArr != NULL);//NULl대비
    this->size = size;
    this->tos = 0;
}

// void cleanupStack(Stack *this){
// void Stack::cleanupStack(){
Stack::~Stack(){
    // free(this->pArr);
    delete [] this->pArr;
}


// void push(Stack *this, int data){
void Stack::push(int data){
    assert(this->tos != this->size);

    this->pArr[this->tos] = data;
    ++this->tos;
}

// int pop(Stack *this){
int Stack::pop(){
    assert(this->tos != 0);

    --this->tos;
    return this->pArr[this->tos];
}

