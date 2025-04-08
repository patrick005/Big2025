#include "stack.h"
#include <stdlib.h>

void initStack(Stack *ps){
    ps->tos = 0;
}

void push(Stack *ps, int data){
    // s.array[s.tos] = data;
    // ++s.tos;

    //full 예외처리
    if(ps->tos >= STACKSIZE ){
        fprintf(stderr, "stack is full.\n");
        exit(1);
    }
    (*ps).array[(*ps).tos] = data;
    ++(*ps).tos;
    //ps->array[ps->tos] = data;
    //++ps->tos;
}

int pop(Stack *ps){
    // --s.tos;
    // return s.array[s.tos];

    //empty 예외처리
    if (ps->tos <= 0){
        fprintf(stderr, "stack is empty.\n");
        exit(2);
    }
    
    --(*ps).tos;
    return (*ps).array[(*ps).tos];
}

