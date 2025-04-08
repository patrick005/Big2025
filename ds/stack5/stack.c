#include "stack.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void initStack(Stack *ps, int size, int eleSize){
    // ps->pArr = malloc(sizeof(int)*size);
    ps->pArr = malloc(eleSize * size);
    assert(ps->pArr != NULL);//NULl대비
    
    ps->eleSize = eleSize;
    ps->size = size;
    ps->tos = 0;
}

//cleanup
void cleanupStack(Stack *ps){
    free(ps->pArr);
}

// void push(Stack *ps, int data){
void push(Stack *ps, const void *pData/*, int eleSize*/){

    assert(ps->tos != ps->size);

    // ps->pArr[ps->tos] = data;
    // memcpy(&ps->pArr[ps->tos], pData, ps->eleSize); // ps->pArr[ps->tos]==*(ps->pArr + ps -> tos)
    memcpy((unsigned char *)ps->pArr + ps->tos * ps->eleSize, pData, ps->eleSize);
    ++ps->tos;
}

// int pop(Stack *ps, int *pData){
void pop(Stack *ps, void *pData/*, int eleSize*/){
    assert(ps->tos != 0);

    --ps->tos;
    // *pData = ps->pArr[ps->tos];//리턴 없애고 포인터를 스캔처럼사용
    // memcpy(pData, &ps->pArr[ps->tos], ps->eleSize);
    memcpy(pData, (unsigned char *)ps->pArr + ps->tos * ps->eleSize, ps->eleSize);
}


