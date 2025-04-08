#include "stack.h"
#include <stdlib.h>
#include <assert.h>

void initStack(Stack *ps, int size){
    ps->pArr = malloc(sizeof(int)*size);
    assert(ps->pArr != NULL);//NULl대비
    ps->size = size;
    ps->tos = 0;
}

//cleanup
void cleanupStack(Stack *ps){
    free(ps->pArr);
}


void push(Stack *ps, int data){
    //full 예외처리
    // if(ps->tos >= STACKSIZE ){
    //     fprintf(stderr, "stack is full.\n");
    //     exit(1);
    // }
    assert(ps->tos != ps->size);

    ps->pArr[ps->tos] = data;
    ++ps->tos;
}

int pop(Stack *ps){
    //empty 예외처리
    // if (ps->tos <= 0){
    //     fprintf(stderr, "stack is empty.\n");
    //     exit(2);
    // }
    assert(ps->tos != 0);

    --ps->tos;
    return ps->pArr[ps->tos];
}

